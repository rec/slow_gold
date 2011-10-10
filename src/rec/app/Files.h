#ifndef __REC_APP_APPDIRECTORY__
#define __REC_APP_APPDIRECTORY__

#include "rec/base/base.h"

namespace rec {
namespace app {

// Set the name of the application ("SlowGold").  You may only call this once.
void setName(const String&);
const String& getName();

// Get the root directory to store files.
File getAppDirectory();
File getAppFile(const String&);

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_APPDIRECTORY__
