#include "rec/command/TargetManager.h"

#include "rec/app/Files.h"
#include "rec/command/Command.h"
#include "rec/command/map/Keyboard.xml.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/data/Data.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

TargetManager::TargetManager()
    : lastInvocation_(0),
      disabled_(false) {
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
  for (i = table_.begin(); i != table_.end(); ++i) {
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
    LOG(DFATAL) << "No getCommandInfo" << commandName(id);

  if (!info.shortName.isNotEmpty())
    LOG(DFATAL) << "No name for " << commandName(id);
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
  DLOG(INFO) << "addCallback: " << commandName(id);
  ptr<Callback> callback(cb);
  if (!(category.isNotEmpty() && name.isNotEmpty() && desc.isNotEmpty())) {
    LOG(DFATAL) << "Can't add " << commandName(id)
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
    LOG(DFATAL) << "Added command twice: " << commandName(id);

  cr->callback_.reset(callback.transfer());
}

ApplicationCommandInfo* TargetManager::getInfo(CommandID id) {
  return find(id)->info_.get();
}

void TargetManager::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
                                   const String& name) {
  CommandRecord* cr = find(id);
  if (!cr->info_) {
    LOG(DFATAL) << "Can't add item " << CommandIDEncoder::commandIDName(id);
    return;
  }

  ApplicationCommandInfo* info = cr->info_.get();

  if (name.length())
    info->shortName = name;
  else if (cr->setter_)
    info->shortName = str(cr->setter_->menuName());

  if (!info->shortName.length())
    LOG(DFATAL) << "No name for command " << commandName(id);
  info->setActive(enable);
  menu->addCommandItem(commandManager(), id, name);
}

CommandRecord* TargetManager::find(CommandID id) {
  return command::find(&table_, id);
}

void TargetManager::addCallbacks() {
  CommandRecordTable::iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    CommandRecord* cr = i->second;
    const Command* command = cr->command_.get();
    if (!command) {
      LOG(DFATAL) << "No command for ID " << i->first;

    } else if (!cr->callback_) {
      LOG(DFATAL) << "No callback for ID " << i->first;

    } else {
      const String& menu = command->desc().menu_size() ?
          str(command->desc().menu(0)) : String();
      const String& desc = str(command->desc().full());
      const String& category = str(command->category());

      addCallback(i->first, cr->callback_.get(), menu, category, desc);
    }
  }

}

}  // namespace command
}  // namespace rec
