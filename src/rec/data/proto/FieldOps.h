#ifndef __REC_DATA_PROTO_FIELDOPS__
#define __REC_DATA_PROTO_FIELDOPS__

#include "rec/data/Operation.pb.h"
#include "rec/data/proto/MessageField.h"

namespace rec {
namespace data {

class MessageField;

namespace proto {

bool apply(MessageField*, const Operation&);
bool undo(MessageField*, const Operation&, Operation*);
bool copyTo(const MessageField& f, ValueProto* value);

}  // namespace proto
}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_FIELDOPS__
