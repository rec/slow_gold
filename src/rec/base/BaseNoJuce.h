#ifndef __REC_BASE_BASE__
#define __REC_BASE_BASE__

#include <string>
#include <vector>

#include <glog/logging.h>

#include "rec/base/disallow.h"
#include "rec/base/ptr.h"
#include "rec/base/types.h"

namespace google {
namespace protobuf {
class Message;
}
}

namespace rec {
namespace util {
namespace listener {
}
namespace file {
class VolumeFile;
}
}  // namespace util
}  // namespace rec

namespace rec {

typedef std::string string;
typedef unsigned int uint;

typedef google::protobuf::Message Message;

using namespace util::listener;
using namespace util;

using util::file::VolumeFile;
using std::vector;

enum Orientation {HORIZONTAL, VERTICAL};

inline Orientation inverse(Orientation o) {
  return (o == HORIZONTAL) ? VERTICAL : HORIZONTAL;
}

}  // namespace rec

#endif  // __REC_BASE_BASENOJUCE__
