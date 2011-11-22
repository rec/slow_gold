#ifndef __REC_SLOW_SETTERCALLBACKS__
#define __REC_SLOW_SETTERCALLBACKS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

class Instance;

void addSetterCallbacks(command::CallbackTable*, Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SETTERCALLBACKS__
