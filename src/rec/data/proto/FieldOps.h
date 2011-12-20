#ifndef __REC_DATA_PROTO_FIELDOPS__
#define __REC_DATA_PROTO_FIELDOPS__

#include "rec/data/Value.h"

namespace rec {
namespace data {

class Address;
class MessageField;
class Operation;
class ValueProto;

bool apply(const MessageField&, const Operation&);
bool copyTo(const MessageField&, ValueProto*);

Value getValueWithAddress(const Address&, const Message&);
void setValueWithAddress(const Address&, Message*, const ValueProto&);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_FIELDOPS__
