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
class VirtualFile;
}

}  // namespace util

namespace proto {
namespace arg {

struct Address;
class Setter;
class Value;

}  // namespace arg
}  // namespace proto

typedef std::string string;
typedef unsigned int uint;

typedef google::protobuf::Message Message;

using namespace util::listener;
using namespace util;

using util::file::VirtualFile;
using std::vector;
using proto::arg::Address;
using proto::arg::Setter;
using proto::arg::Value;

enum Orientation {HORIZONTAL, VERTICAL};

inline Orientation inverse(Orientation o) {
  return (o == HORIZONTAL) ? VERTICAL : HORIZONTAL;
}

inline double samplesToTime(int samples, double sampleRate = 44100.0) {
  return samples / sampleRate;
}

}  // namespace rec

#endif  // __REC_BASE_BASENOJUCE__
