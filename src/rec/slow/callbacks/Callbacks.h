#ifndef __REC_SLOW_CALLBACKS__
#define __REC_SLOW_CALLBACKS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

class Instance;

static const int REPEATED_COUNT = 10;

void addSlowCallbacks(Instance*, command::CommandRecordTable*,
                      int repeat = REPEATED_COUNT);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CALLBACKS__
