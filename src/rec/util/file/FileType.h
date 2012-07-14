#ifndef __REC_UTIL_FILE_FILETYPE__
#define __REC_UTIL_FILE_FILETYPE__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

const File& getFileTypeDirectory(VirtualFile::Type);
const char* getFileTypeName(VirtualFile::Type);
VirtualFile::Type getFileType(const File&);
void moveOldAbsoluteDirectoriesToTypeRelative();

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_FILETYPE__
