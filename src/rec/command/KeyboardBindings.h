#ifndef __REC_COMMAND_KEYBOARDBINDINGS__
#define __REC_COMMAND_KEYBOARDBINDINGS__

#include "rec/base/base.h"

namespace rec {
namespace command {

class CommandRecordTable;

void saveKeyboardBindings(ApplicationCommandManager*);
void loadKeyboardBindings(const CommandRecordTable&,
                          ApplicationCommandManager*);
void clearKeyboardBindings(const CommandRecordTable&,
                          ApplicationCommandManager*);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYBOARDBINDINGS__
