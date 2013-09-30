#ifndef __REC_SLOW_REPEATEDCALLBACKS__
#define __REC_SLOW_REPEATEDCALLBACKS__

#include "rec/base/base.h"

namespace rec {

namespace program { class Program; }

namespace slow {

void addRepeatedCallbacks(program::Program*, int repeat);
void addSelectionCallbacks(program::Program*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REPEATEDCALLBACKS__
