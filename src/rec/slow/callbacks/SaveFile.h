#ifndef __REC_SLOW_CALLBACKS_SAVEFILE__
#define __REC_SLOW_CALLBACKS_SAVEFILE__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Instance;

void saveFile(Instance* instance);
void saveFileSelection(Instance* instance);

struct SaveFile {
  static void translateAll();
};


}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CALLBACKS_SAVEFILE__
