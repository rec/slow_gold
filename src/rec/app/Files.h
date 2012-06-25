#ifndef __REC_APP_APPDIRECTORY__
#define __REC_APP_APPDIRECTORY__

#include "rec/base/base.h"

namespace rec {
namespace app {

// Set the name of the application ("SlowGold").  You may only call this once.
void setApplicationName(const String&);
String getApplicationName();

// Get the root directory to store files.
File getCompanyDirectory();
File getAppDirectory();
File getAppFile(const String&);

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_APPDIRECTORY__
