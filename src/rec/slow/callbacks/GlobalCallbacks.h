#ifndef __REC_SLOW_GLOBALCOMMANDS__
#define __REC_SLOW_GLOBALCOMMANDS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

void addGlobalCallbacks(command::CommandRecordTable* t);
void requestSupport();

struct GlobalCallbacks {
  static void translateAll();
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GLOBALCOMMANDS__
