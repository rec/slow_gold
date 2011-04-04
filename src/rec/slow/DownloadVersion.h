#ifndef __REC_SLOW_DOWNLOADVERSION__
#define __REC_SLOW_DOWNLOADVERSION__

#include "rec/base/base.h"

namespace rec {
namespace slow {

// Returns true if a new version was downloaded.
bool downloadNewVersionIfNeeded(const String& version, const String& name);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_DOWNLOADVERSION__
