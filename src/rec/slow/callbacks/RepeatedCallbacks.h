#ifndef __REC_SLOW_REPEATEDCALLBACKS__
#define __REC_SLOW_REPEATEDCALLBACKS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

struct Instance;

void addRepeatedCallbacks(command::CallbackTable*, Instance*, int repeat);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REPEATEDCALLBACKS__
