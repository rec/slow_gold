#ifndef __REC_DATA_PROTO_FIELDOPS__
#define __REC_DATA_PROTO_FIELDOPS__

#include "rec/base/base.h"

namespace rec {
namespace data {

class Address;
class MessageField;
class Operation;
class ValueProto;

bool apply(const MessageField&, const Operation&);
bool copyTo(const MessageField&, ValueProto*);

bool getValueWithAddress(const Address&, const Message&, ValueProto*);
bool setValueWithAddress(const Address&, Message*, const ValueProto&);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_FIELDOPS__
