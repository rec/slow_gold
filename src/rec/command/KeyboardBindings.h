#ifndef __REC_COMMAND_KEYBOARDBINDINGS__
#define __REC_COMMAND_KEYBOARDBINDINGS__

#include "rec/base/base.h"

namespace rec {
namespace command {

class CommandMapProto;

void loadKeyboardBindings(ApplicationCommandManager*);
void saveKeyboardBindings(const CommandMapProto&);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYBOARDBINDINGS__
