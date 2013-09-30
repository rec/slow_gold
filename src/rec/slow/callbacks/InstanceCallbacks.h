#ifndef __REC_SLOW_TARGETCOMMANDS__
#define __REC_SLOW_TARGETCOMMANDS__

#include "rec/base/base.h"

namespace rec {

namespace program { class Program; }

namespace slow {

void addInstanceCallbacks(program::Program*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_TARGETCOMMANDS__
