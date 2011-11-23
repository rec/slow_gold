#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/util/thread/Callback.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandItemSetter.h"

namespace rec {
namespace command {

typedef std::map<CommandID, Command*> CommandTable;
typedef std::map<CommandID, Callback*> CallbackTable;
typedef std::map<CommandID, CommandItemSetter*> SetterTable;

const CommandTable toCommandTable(const Commands&);
const Commands fromCommandTable(const CommandTable&);

struct CommandContext {
  CommandTable commands_;
  SetterTable setters_;
  CallbackTable callbacks_;
};

const CommandContext& getCommandContext();

inline const Commands getCommands() {
  return fromCommandTable(getCommandContext().commands_);
}

// Call to recalculate commands if Access changes for the user.
void recalculate();

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
