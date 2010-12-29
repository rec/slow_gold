#ifndef __REC_UTIL_FILE_GETVOLUMES__
#define __REC_UTIL_FILE_GETVOLUMES__

#include <vector>

#include "rec/base/base.h"
#include "rec/util/file/VolumeFile.pb.h"

namespace rec {
namespace util {
namespace file {

VolumeFileList getVolumes();

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_GETVOLUMES__
