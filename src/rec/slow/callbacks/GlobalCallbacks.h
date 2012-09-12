#ifndef __REC_SLOW_GLOBALCOMMANDS__
#define __REC_SLOW_GLOBALCOMMANDS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CallbackTable; }

namespace slow {

void addGlobalCallbacks(command::CallbackTable* t);
void requestSupport();

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GLOBALCOMMANDS__
