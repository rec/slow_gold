#ifndef __REC_UTIL_FILE_VIRTUALFILE__
#define __REC_UTIL_FILE_VIRTUALFILE__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

// Converts a file on the file system to a virtual file reference, which might
// be relative to one of the special directories.
const VirtualFile toVirtualFile(const File&, bool useSpecial = true);

// The inverse of toVirtualFile.
const File toRealFile(const VirtualFile&);

// Given a VirtualFile, return the actual directory that shadows it.
const File getShadowDirectory(const VirtualFile&);

inline const VirtualFile makeVirtualFile(VirtualFile::Type type) {
  VirtualFile vf;
  vf.set_type(type);
  return vf;
}

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_VIRTUALFILE__
