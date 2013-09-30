#ifndef __REC_SLOW_CALLBACKS_APPLYCALLBACKS__
#define __REC_SLOW_CALLBACKS_APPLYCALLBACKS__

#include "rec/base/base.h"

namespace rec {

namespace program { class Program; }

namespace slow {

void addApplyCallbacks(program::Program*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CALLBACKS_APPLYCALLBACKS__
