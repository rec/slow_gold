#ifndef __REC_SLOW_GUISETTINGS__
#define __REC_SLOW_GUISETTINGS__

#include "rec/base/base.h"

namespace rec {
namespace slow {

enum SaveOrOpen {SAVE_FILE, OPEN_FILE};

File browseForFile(const String& msg, const File& startFile, SaveOrOpen save);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GUISETTINGS__
