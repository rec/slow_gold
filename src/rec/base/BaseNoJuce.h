#ifndef __REC_BASE_BASE__
#define __REC_BASE_BASE__

#include <string>

#include "rec/base/disallow.h"
#include "rec/base/scoped_ptr.h"
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

namespace util {}
using namespace util;

namespace widget {
namespace tree {

class VolumeFile;

}  // namespace tree
}  // namespace widget

using VolumeFile;

}  // namespace rec

#endif  // __REC_BASE_BASENOJUCE__
