#ifndef __REC_UTIL_FILE_VIRTUALFILE__
#define __REC_UTIL_FILE_VIRTUALFILE__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

const VirtualFile makeVirtualFile(VirtualFile::Type);

const File getShadowDirectory(const VirtualFile&);

const VirtualFile toCompactVirtualFile(const File&);
const VirtualFile toOriginalVirtualFile(const File&);
const VirtualFile toVirtualFile(const File&);

const File toRealFile(const VirtualFile&);

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_VIRTUALFILE__
