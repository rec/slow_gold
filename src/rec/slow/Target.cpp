#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/CommandTarget.h"
#include "rec/command/map/MidiCommandMap.h"
#include "rec/data/DataOps.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/MethodListener.h"

using namespace rec::command;

namespace rec {
namespace slow {

bool Target::perform(const InvocationInfo& invocation) {
	if (invocation.commandID != Command::ABOUT_THIS_PROGRAM) {
    if (window())
      thread::callAsync(window(), &app::Window::stopAboutWindow);
  }

  Lock l(lock_);
  if (enabled_ == DISABLE)
    return true;

  // TODO: should we really be creating items here?
  CommandRecord* cr = commandRecordTable()->findOrCreate(invocation.commandID);
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

  CommandRecord* cr = commandRecordTable()->findOrCreate(id);
  if (cr->callback_)
    LOG(DFATAL) << "Add command twice: " << CommandIDEncoder::commandIDName(id);

  cr->callback_.reset(callback.transfer());
}

void Target::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
                            const String& name, int flags) {
  CommandRecord* cr = commandRecordTable()->findOrCreate(id);
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
  menu->addCommandItem(applicationCommandManager(), id);
}

void Target::operator()(CommandID id) {
  if (!applicationCommandManager()->invokeDirectly(id, false))
    LOG(DFATAL) << "Failed to invoke " << CommandIDEncoder::commandIDName(id);
}

void Target::operator()(Enable enabled) {
  Lock l(lock_);
  enabled_ = enabled;
}

}  // namespace slow
}  // namespace rec

