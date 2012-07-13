#ifndef __REC_UTIL_FILE_DISPLAYFILE__
#define __REC_UTIL_FILE_DISPLAYFILE__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace file {

const String getFilename(const VirtualFile&);
const String getDisplayName(const VirtualFile&);
const String getFullDisplayName(const VirtualFile&);

inline const string toString(const VirtualFile& f) {
  return str(getFullDisplayName(f));
}

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_DISPLAYFILE__
