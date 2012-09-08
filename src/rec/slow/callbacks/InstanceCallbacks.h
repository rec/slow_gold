#ifndef __REC_SLOW_TARGETCOMMANDS__
#define __REC_SLOW_TARGETCOMMANDS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

class Instance;

void addInstanceCallbacks(command::CommandRecordTable*);

struct InstanceCallbacks {
  static void registerAllTranslations();
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_TARGETCOMMANDS__
