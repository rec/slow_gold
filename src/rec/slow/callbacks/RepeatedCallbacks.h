#ifndef __REC_SLOW_REPEATEDCALLBACKS__
#define __REC_SLOW_REPEATEDCALLBACKS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CallbackTable; }

namespace slow {

void addRepeatedCallbacks(command::CallbackTable*, int repeat, bool newStyle);
void addSelectionCallbacks(command::CallbackTable*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REPEATEDCALLBACKS__
