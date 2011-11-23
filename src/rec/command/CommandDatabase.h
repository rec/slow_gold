#ifndef __REC_COMMAND_COMMANDDATABASE__
#define __REC_COMMAND_COMMANDDATABASE__

#include "rec/base/base.h"

namespace rec {
namespace command {

void insertSingle(CommandTable*);
void insertRepeated(CommandTable*);
void insertSetters(CommandContext*, Listener<None>*);
void mergeKeyPresses(CommandTable*, const Access&);
void mergeDescription(CommandTable*, const Command&);
void mergeDescriptions(CommandTable*, const Access&);
void removeEmpties(CommandTable*);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATABASE__
