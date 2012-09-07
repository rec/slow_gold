#ifndef __REC_SLOW_SELECTIONCALLBACKS__
#define __REC_SLOW_SELECTIONCALLBACKS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

class Instance;

void addSelectionCallbacks(command::CommandRecordTable*, Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SELECTIONCALLBACKS__
