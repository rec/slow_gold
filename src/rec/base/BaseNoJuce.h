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

}  // namespace protobuf
}  // namespace google

namespace rec {

typedef std::string string;
typedef unsigned int uint;

typedef google::protobuf::Message Message;

namespace util {
namespace file {

class VolumeFile;

}  // namespace file
}  // namespace util

using namespace util;

using util::file::VolumeFile;
using std::vector;

}  // namespace rec


#endif  // __REC_BASE_BASENOJUCE__
