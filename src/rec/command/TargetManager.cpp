#include "rec/command/TargetManager.h"

#include "rec/app/Files.h"
#include "rec/command/Command.h"
#include "rec/command/map/Keyboard.xml.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

using slow::Position;

TargetManager::TargetManager(Component* c, CommandRecordTable* table)
    : table_(table),
      lastInvocation_(0),
      disabled_(false) {
  c->addKeyListener(commandManager_.getKeyMappings());
  commandManager_.setFirstCommandTarget(this);
}

TargetManager:: ~TargetManager() {}

void TargetManager::registerAllCommandsForTarget() {
  commandManager_.registerAllCommandsForTarget(this);
  loadKeyboardBindings(this);
}

void TargetManager::getAllCommands(juce::Array<CommandID>& commands) {
  commands.clear();
  CommandRecordTable::const_iterator i;
  for (i = table_->begin(); i != table_->end(); ++i) {
    if (i->second->callback_)
      commands.add(i->first);
  }
}

void TargetManager::getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
  Lock l(lock_);
  CommandRecord* cr = find(id);
  if (cr->info_)
    info = *(cr->info_);
  else
    LOG(ERROR) << "No getCommandInfo" << slow::Position::commandIDName(id);

  if (!info.shortName.isNotEmpty())
    LOG(ERROR) << "No name for " << slow::Position::commandIDName(id);
}

bool TargetManager::perform(const InvocationInfo& invocation) {
  Lock l(lock_);
  if (disabled_)
    return true;

  CommandRecord* cr = find(invocation.commandID);
  if (!cr->callback_)
    return false;

  lastInvocation_ = invocation;
  (*(cr->callback_))();
  return true;
}

InvocationInfo TargetManager::lastInvocation() const {
  Lock l(lock_);
  return lastInvocation_;
}

void TargetManager::addCallback(CommandID id, Callback* cb,
                                const String& name,
                                const String& category,
                                const String& desc) {
  ptr<Callback> callback(cb);
  if (!(category.isNotEmpty() && name.isNotEmpty() && desc.isNotEmpty())) {
    LOG(ERROR) << "Can't add " << slow::Position::commandIDName(id)
               << ", " << name << ", " << desc;
    return;
  }

  ApplicationCommandInfo info(id);
  int flags = 0;
  if (category == "" || category == "(None)")
    flags = ApplicationCommandInfo::hiddenFromKeyEditor;
  info.setInfo(name, desc, category, flags);

  CommandRecord* cr = find(id);
  if (cr->callback_)
    LOG(ERROR) << "Added command twice: " << id;

  cr->callback_.reset(callback.transfer());
}

ApplicationCommandInfo* TargetManager::getInfo(CommandID id) {
  return find(id)->info_.get();
}

void TargetManager::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
                                   const String& name) {
  CommandRecord* cr = find(id);
  if (!cr->info_) {
    LOG(ERROR) << "Can't add item " << Position::commandIDName(id);
    return;
  }

  ApplicationCommandInfo* info = cr->info_.get();

  if (name.length())
    info->shortName = name;
  else if (cr->setter_)
    info->shortName = str(cr->setter_->menuName());

  if (!info->shortName.length())
    LOG(ERROR) << "No name for command " << slow::Position::commandIDName(id);
  info->setActive(enable);
  menu->addCommandItem(commandManager(), id, name);
}

CommandRecord* TargetManager::find(CommandID id) {
  return command::find(table_.get(), id);
}

}  // namespace command
}  // namespace rec
