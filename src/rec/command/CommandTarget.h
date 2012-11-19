#ifndef __REC_COMMAND_COMMANDTARGET__
#define __REC_COMMAND_COMMANDTARGET__

#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/slow/Target.h"
#include "rec/slow/HasInstance.h"

namespace rec {
namespace command {

class CommandTarget : public ApplicationCommandTarget,
                      public slow::HasInstance {
 public:
  CommandTarget(slow::Instance* i) : slow::HasInstance(i) {}
  virtual ApplicationCommandTarget* getNextCommandTarget() { return NULL; }

  virtual void getAllCommands(juce::Array<CommandID>& commands) {
    commandRecordTable()->getAllCommands(&commands);
  }

  virtual void getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
    // TODO: should we really be creating items here?
    info = *commandRecordTable()->findOrCreate(id)->getInfo();

    if (!info.shortName.isNotEmpty())
      LOG(ERROR) << "No name for " << CommandIDEncoder::commandIDName(id);

    if ((info.flags & ApplicationCommandInfo::isDisabled))
      DLOG(INFO) << CommandIDEncoder::commandIDName(id) << " DISABLED";
  }

  virtual bool perform(const InvocationInfo& info) {
    return instance_->target_->perform(info);
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandTarget);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDTARGET__
