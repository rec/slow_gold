#include <algorithm>

#include "rec/util/file/CompareFile.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

bool lessThan(const VirtualFile& x, const VirtualFile& y) {
  if (x.type() < y.type())
    return true;

  if (x.type() > y.type())
    return false;

  if (x.volume_name() < y.volume_name())
    return true;

  if (x.volume_name() > y.volume_name())
    return false;

  for (int i = 0; ; i++) {
    bool xDone = (i >= x.path_size());
    bool yDone = (i >= y.path_size());
    if (xDone)
      return !yDone;

    if (yDone)
      return false;

    if (x.path(i) < y.path(i))
      return true;

    if (y.path(i) < x.path(i))
      return false;
  }
}

void sort(VirtualFileList* v) {
  std::sort(v->mutable_file()->begin(), v->mutable_file()->end(), lessThan);
}

}  // namespace file
}  // namespace util
}  // namespace rec

