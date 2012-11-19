#ifndef __REC_COMMAND_COMMANDTARGET__
#define __REC_COMMAND_COMMANDTARGET__

#include "rec/command/CommandRecord.h"
#include "rec/command/TargetManager.h"

namespace rec {
namespace command {

class CommandTarget : public ApplicationCommandTarget {
 public:
  explicit CommandTarget(TargetManager* tm, CommandRecordTable* table)
      : targetManager_(tm), table_(table) {
  }

  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

  virtual void getAllCommands(juce::Array<CommandID>& commands) {
    table_->getAllCommands(&commands);
  }

  virtual void getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
    info = *targetManager_->find(id)->getInfo();

    if (!info.shortName.isNotEmpty())
      LOG(ERROR) << "No name for " << CommandIDEncoder::commandIDName(id);
    if ((info.flags & ApplicationCommandInfo::isDisabled))
      DLOG(INFO) << CommandIDEncoder::commandIDName(id) << " DISABLED";
  }

  virtual bool perform (const InvocationInfo& info) {
    return targetManager_->perform(info);
  }

 private:
  TargetManager* const targetManager_;
  CommandRecordTable* const table_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandTarget);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDTARGET__
