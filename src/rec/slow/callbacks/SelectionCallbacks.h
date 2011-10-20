#ifndef __REC_SLOW_SELECTIONCALLBACKS__
#define __REC_SLOW_SELECTIONCALLBACKS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

class Instance;

void addSelectionCallbacks(command::CallbackTable*, Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SELECTIONCALLBACKS__
