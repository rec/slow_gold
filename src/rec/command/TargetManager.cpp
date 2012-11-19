#include "rec/command/TargetManager.h"

#include "rec/app/Files.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandDatabase.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/CommandTarget.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/data/Data.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

TargetManager::TargetManager(CommandData* commandData,
                             ApplicationCommandManager* commandManager,
                             CommandRecordTable* table,
                             ApplicationCommandTarget* target)
    : lastInvocation_(0),
      disabled_(false),
      commandData_(commandData),
      commandManager_(commandManager),
      table_(table),
      target_(target) {
  commandManager_->setFirstCommandTarget(target_);
}

TargetManager:: ~TargetManager() {}

bool TargetManager::perform(const InvocationInfo& invocation) {
	if (invocation.commandID != Command::ABOUT_THIS_PROGRAM)
    broadcast(None());

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

void TargetManager::addCallback(CommandID id,
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

void TargetManager::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
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
  if (!enable)
    DLOG(INFO) << CommandIDEncoder::commandIDName(id);

  info->setActive(enable);
  menu->addCommandItem(commandManager_, id);
}

CommandRecord* TargetManager::find(CommandID id) {
  Lock l(lock_);
  return table_->find(id);
}

void TargetManager::addCommands() {
  fillCommandRecordTable(table_, *commandData_);
  commandManager_->registerAllCommandsForTarget(target_);
  loadKeyboardBindings(this);
}

}  // namespace command
}  // namespace rec
