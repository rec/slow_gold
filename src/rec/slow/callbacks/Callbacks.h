#ifndef __REC_SLOW_CALLBACKS__
#define __REC_SLOW_CALLBACKS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

struct Instance;

static const int REPEATED_COUNT = 10;

command::CallbackTable* createCallbackTable(Instance*,
                                            int repeat = REPEATED_COUNT);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CALLBACKS__
