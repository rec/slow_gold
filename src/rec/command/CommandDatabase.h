#ifndef __REC_COMMAND_COMMANDDATABASE__
#define __REC_COMMAND_COMMANDDATABASE__

#include "rec/command/Command.h"

namespace rec {
namespace command {

class Access;

void insertSingle(CommandRecordTable*);
void insertRepeated(CommandRecordTable*);
void insertSetters(CommandRecordTable*, Listener<None>*);
void mergeKeyPresses(CommandRecordTable*, const Access&);
void mergeDescriptions(CommandRecordTable*, const Access&);
void removeEmpties(CommandRecordTable*);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATABASE__
