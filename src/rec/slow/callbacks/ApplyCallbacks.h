#ifndef __REC_SLOW_CALLBACKS_APPLYCALLBACKS__
#define __REC_SLOW_CALLBACKS_APPLYCALLBACKS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CallbackTable; }

namespace slow {

void addApplyCallbacks(command::CallbackTable*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CALLBACKS_APPLYCALLBACKS__
