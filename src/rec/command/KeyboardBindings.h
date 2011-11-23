#ifndef __REC_COMMAND_KEYBOARDBINDINGS__
#define __REC_COMMAND_KEYBOARDBINDINGS__

#include "rec/base/base.h"

namespace rec {
namespace command {

void saveKeyboardBindings(ApplicationCommandManager*);
void loadKeyboardBindings(ApplicationCommandManager*);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYBOARDBINDINGS__