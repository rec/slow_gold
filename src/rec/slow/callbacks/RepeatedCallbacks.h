#ifndef __REC_SLOW_REPEATEDCALLBACKS__
#define __REC_SLOW_REPEATEDCALLBACKS__

#include "rec/command/CommandIDEncoder.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

void addRepeatedCallbacks(command::CommandRecordTable*, int repeat);
void addSelectionCallbacks(command::CommandRecordTable*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REPEATEDCALLBACKS__
