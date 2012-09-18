#ifndef __REC_COMMAND_COMMANDDATABASE__
#define __REC_COMMAND_COMMANDDATABASE__

#include "rec/command/CommandRecord.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CommandData;
class CommandRecordTable;

void fillCommandRecordTable(CommandRecordTable*, const CommandData&);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATABASE__
