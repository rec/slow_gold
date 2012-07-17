#ifndef __REC_UTIL_FILE_MOVEFILE__
#define __REC_UTIL_FILE_MOVEFILE__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

void moveTypeDirectory(VirtualFile::Type type, const File& special);
void moveGlobalFiles();
void moveKeyboardFile();

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_MOVEFILE__
