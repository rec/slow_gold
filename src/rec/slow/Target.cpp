#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandDatabase.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandTarget.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/MidiCommandMap.h"
#include "rec/data/DataOps.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::command;

namespace rec {
namespace slow {

Target::Target(Instance* i)
    : HasInstance(i),
      disabled_(false) {
  target_.reset(new CommandTarget(this, &table_));
  commandData_.reset(slow::createSlowCommandData(i));
  commandManager_.setFirstCommandTarget(target_.get());
  i->window_->addKeyListener(commandManager_.getKeyMappings());

  this->addListener(this);  // TODO: do I need this?!
}

Target::~Target() {}

void Target::addCommands() {
  command::fillCommandRecordTable(&table_, *commandData_);
  commandManager_.registerAllCommandsForTarget(target_.get());
  loadKeyboardBindings(table_, &commandManager_);
  window()->getAppleMenu()->addCommandItem(&commandManager_,
                                           Command::ABOUT_THIS_PROGRAM);
}

void Target::operator()(None) {
  if (window())
    thread::callAsync(window(), &app::Window::stopAboutWindow);
}

bool Target::perform(const InvocationInfo& invocation) {
	if (invocation.commandID != Command::ABOUT_THIS_PROGRAM)
    broadcast(None());

  Lock l(lock_);
  if (disabled_)
    return true;

  CommandRecord* cr = find(invocation.commandID);
  if (!cr->callback_)
    return false;

  (*(cr->callback_))();
  return true;
}

void Target::addCallback(CommandID id,
                                Callback* cb,
                                const String& name,
                                const String& category,
                                const String& desc) {
  ptr<Callback> callback(cb);
  if (!(category.isNotEmpty() && name.isNotEmpty() && desc.isNotEmpty())) {
    LOG(DFATAL) << "Can't add " << CommandIDEncoder::commandIDName(id)
               << ", " << name << ", " << desc;
    return;
  }

  ApplicationCommandInfo info(id);
  int flags = 0;
  if (category == "" || category == "(None)")
    flags += ApplicationCommandInfo::hiddenFromKeyEditor;
  info.setInfo(name, desc, category, flags);

  CommandRecord* cr = find(id);
  if (cr->callback_)
    LOG(DFATAL) << "Add command twice: " << CommandIDEncoder::commandIDName(id);

  cr->callback_.reset(callback.transfer());
}

void Target::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
                                   const String& name, int flags) {
  CommandRecord* cr = find(id);
  ApplicationCommandInfo* info = cr->getInfo();

  if (name.length())
    info->shortName = name;
  else if (cr->setter_)
    info->shortName = str(cr->setter_->menuName());

  if (!info->shortName.length()) {
    LOG(ERROR) << "No name for " << CommandIDEncoder::commandIDName(id);
    info->shortName = "(error)";
  }
  if (flags >= 0)
    info->flags = flags;
  if (false && !enable)
    DLOG(INFO) << CommandIDEncoder::commandIDName(id);

  info->setActive(enable);
  menu->addCommandItem(&commandManager_, id);
}

command::CommandRecord* Target::find(CommandID id) {
  Lock l(lock_);
  return table_.find(id);
}

void Target::operator()(CommandID id) {
  if (!commandManager_.invokeDirectly(id, false))
    LOG(DFATAL) << "Failed to invoke " << CommandIDEncoder::commandIDName(id);
}

void Target::operator()(bool d) {
  Lock l(lock_);
  disabled_ = d;
}


}  // namespace slow
}  // namespace rec

