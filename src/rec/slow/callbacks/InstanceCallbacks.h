#ifndef __REC_SLOW_TARGETCOMMANDS__
#define __REC_SLOW_TARGETCOMMANDS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CallbackTable; }

namespace slow {

void addInstanceCallbacks(command::CallbackTable*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_TARGETCOMMANDS__
