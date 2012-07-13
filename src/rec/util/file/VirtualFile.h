#ifndef __REC_UTIL_FILE_VIRTUALFILE__
#define __REC_UTIL_FILE_VIRTUALFILE__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

const File getShadowDirectory(const VirtualFile&);
const File getShadowFile(const VirtualFile&, const String& child);

const VirtualFile toVirtualFile(const File&);
const File toRealFile(const VirtualFile&);

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_VIRTUALFILE__
