#ifndef __REC_SLOW_CALLBACKS__
#define __REC_SLOW_CALLBACKS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

class Instance;

static const int REPEATED_COUNT = 10;

command::CallbackTable* createCallbackTable(Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CALLBACKS__
