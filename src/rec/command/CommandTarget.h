#ifndef __REC_COMMAND_COMMANDTARGET__
#define __REC_COMMAND_COMMANDTARGET__

#include "rec/command/CommandRecord.h"
#include "rec/command/TargetManager.h"
#include "rec/slow/Target.h"

namespace rec {
namespace command {

class CommandTarget : public ApplicationCommandTarget {
 public:
  explicit CommandTarget(slow::Target* tm, CommandRecordTable* table)
      : target_(tm), table_(table) {
  }

  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

  virtual void getAllCommands(juce::Array<CommandID>& commands) {
    table_->getAllCommands(&commands);
  }

  virtual void getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
    info = *target_->targetManager()->find(id)->getInfo();

    if (!info.shortName.isNotEmpty())
      LOG(ERROR) << "No name for " << CommandIDEncoder::commandIDName(id);
    if ((info.flags & ApplicationCommandInfo::isDisabled))
      DLOG(INFO) << CommandIDEncoder::commandIDName(id) << " DISABLED";
  }

  virtual bool perform(const InvocationInfo& info) {
    return target_->targetManager()->perform(info);
  }

 private:
  slow::Target* const target_;
  CommandRecordTable* const table_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandTarget);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDTARGET__
