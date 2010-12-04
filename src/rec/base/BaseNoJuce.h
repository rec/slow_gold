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

}  // namespace rec

#endif  // __REC_BASE_BASENOJUCE__
