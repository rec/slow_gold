#ifndef __REC_SLOW_DOWNLOADVERSION__
#define __REC_SLOW_DOWNLOADVERSION__

#include "rec/base/base.h"

namespace rec {
namespace slow {

bool downloadNewVersion(const String& name, const String& version);
bool checkForNewMajorVersion(const String& current, const String& name,
                             String* version);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_DOWNLOADVERSION__
