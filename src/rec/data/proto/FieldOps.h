#ifndef __REC_DATA_PROTO_FIELDOPS__
#define __REC_DATA_PROTO_FIELDOPS__

#include "rec/base/base.h"

namespace rec {
namespace data {

class MessageField;
class Operation;
class ValueProto;

bool apply(MessageField*, const Operation&);
bool copyTo(const MessageField& f, ValueProto* value);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_FIELDOPS__
