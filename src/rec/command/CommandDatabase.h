#ifndef __REC_COMMAND_COMMANDDATABASE__
#define __REC_COMMAND_COMMANDDATABASE__

#include "rec/command/Command.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CommandData;

void fillCommandRecordTable(CommandRecordTable*, const CommandData&);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATABASE__
