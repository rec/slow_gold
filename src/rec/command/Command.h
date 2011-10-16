#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace command {

typedef std::map<Command::Type, Command*> CommandTable;

const Command getCommand(Command::Type type);
const CommandTable getCommands();

// Call to recalculate commands if Access changes for the user.
void recalculate();

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
