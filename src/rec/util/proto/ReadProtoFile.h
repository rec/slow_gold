#ifndef __REC_UTIL_PROTO_READPROTOFILE__
#define __REC_UTIL_PROTO_READPROTOFILE__

#include "rec/base/base.h"

namespace rec {
namespace util {

class MessageMaker;

Message* readProtoFile(const File&, const MessageMaker&);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PROTO_READPROTOFILE__
