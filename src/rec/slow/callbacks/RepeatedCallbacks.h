#ifndef __REC_SLOW_REPEATEDCALLBACKS__
#define __REC_SLOW_REPEATEDCALLBACKS__

#include "rec/command/CommandIDEncoder.h"

namespace rec {

namespace command { class CallbackTable; }

namespace slow {

void addRepeatedCallbacks(command::CallbackTable*, int repeat);
void addSelectionCallbacks(command::CallbackTable*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REPEATEDCALLBACKS__
