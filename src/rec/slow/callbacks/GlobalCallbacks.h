#ifndef __REC_SLOW_GLOBALCOMMANDS__
#define __REC_SLOW_GLOBALCOMMANDS__

#include "rec/base/base.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

void addGlobalCallbacks(command::CommandRecordTable* t);
void requestSupport();

struct GlobalCallbacks {
  static void registerAllTranslations();
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GLOBALCOMMANDS__
