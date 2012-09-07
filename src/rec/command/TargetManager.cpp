#include "rec/command/TargetManager.h"

#include "rec/app/Files.h"
#include "rec/command/Command.h"
#include "rec/command/CommandDatabase.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/data/Data.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

namespace {

class CommandTarget : public ApplicationCommandTarget {
 public:
  explicit CommandTarget(TargetManager* tm, CommandRecordTable* table)
      : targetManager_(tm), table_(table) {
  }

  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

  virtual void getAllCommands(juce::Array<CommandID>& commands) {
    commands.clear();
    CommandRecordTable::const_iterator i;
    for (i = table_->begin(); i != table_->end(); ++i) {
      if (i->second->callback_)
        commands.add(i->first);
    }
  }

  virtual void getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
    info = targetManager_->find(id)->info_;

    if (!info.shortName.isNotEmpty())
      LOG(ERROR) << "No name for " << commandName(id);
  }

  virtual bool perform (const InvocationInfo& info) {
    return targetManager_->perform(info);
  }

 private:
  TargetManager* const targetManager_;
  CommandRecordTable* const table_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandTarget);
};

}

TargetManager::TargetManager(CommandData* commandData)
    : lastInvocation_(0),
      disabled_(false),
      commandData_(commandData),
      target_(new CommandTarget(this, &table_)) {
  commandManager_.setFirstCommandTarget(target_.get());
}

TargetManager:: ~TargetManager() {}

void TargetManager::registerAllCommandsForTarget() {
  commandManager_.registerAllCommandsForTarget(target_.get());
  loadKeyboardBindings(this);
}

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
    LOG(DFATAL) << "Can't add " << commandName(id)
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
    LOG(DFATAL) << "Added command twice: " << commandName(id);

  cr->callback_.reset(callback.transfer());
}

ApplicationCommandInfo* TargetManager::getInfo(CommandID id) {
  return &find(id)->info_;
}

void TargetManager::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
                                   const String& name, int flags) {
  CommandRecord* cr = find(id);
  ApplicationCommandInfo* info = &cr->info_;

  if (name.length())
    info->shortName = name;
  else if (cr->setter_)
    info->shortName = str(cr->setter_->menuName());

  if (!info->shortName.length()) {
    LOG(ERROR) << "No name for " << commandName(id);
    info->shortName = "(error)";
  }
  info->setActive(enable);
  if (flags >= 0)
    info->flags = flags;

  menu->addCommandItem(commandManager(), id);
}

CommandRecord* TargetManager::find(CommandID id) {
  Lock l(lock_);
  return table_.find(id);
}

void TargetManager::addCommands() {
  fillCommandRecordTable(&table_, *commandData_);
  registerAllCommandsForTarget();
}

}  // namespace command
}  // namespace rec
