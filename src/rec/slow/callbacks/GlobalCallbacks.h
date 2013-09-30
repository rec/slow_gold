#ifndef __REC_SLOW_GLOBALCOMMANDS__
#define __REC_SLOW_GLOBALCOMMANDS__

#include "rec/base/base.h"

namespace rec {

namespace program { class Program; }

namespace slow {

void addGlobalCallbacks(program::Program* t);
void requestSupport();

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GLOBALCOMMANDS__
