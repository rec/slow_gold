#ifndef __REC_UTIL_FILE_COMPAREFILE__
#define __REC_UTIL_FILE_COMPAREFILE__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace file {

class VirtualFile;
class VirtualFileList;

bool lessThan(const VirtualFile&, const VirtualFile&);
void sort(VirtualFileList*);

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_COMPAREFILE__
