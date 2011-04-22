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
class VirtualFileList;
}

}  // namespace util

namespace proto {
namespace arg {

struct Address;
class Setter;
class Value;

}  // namespace arg
}  // namespace proto

namespace persist {
class UntypedData;
}

typedef std::string string;
typedef unsigned int uint;

typedef google::protobuf::Message Message;

using namespace util::listener;
using namespace util;

using util::file::VirtualFile;
using util::file::VirtualFileList;
using std::vector;
using persist::UntypedData;
using proto::arg::Address;
using proto::arg::Setter;
using proto::arg::Value;

// Useful all over.

typedef int64 SampleTime;
typedef double RealTime;

enum Orientation {HORIZONTAL, VERTICAL};

inline Orientation inverse(Orientation o) {
  return (o == HORIZONTAL) ? VERTICAL : HORIZONTAL;
}

inline RealTime samplesToTime(SampleTime samples, RealTime rate = 44100.0) {
  return samples / rate;
}

inline SampleTime timeToSamples(RealTime time, double rate = 44100.0) {
  return static_cast<SampleTime>(time * rate);
}

}  // namespace rec

#endif  // __REC_BASE_BASENOJUCE__
