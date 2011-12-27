#ifndef __REC_DATA_PROTO_FIELDOPS__
#define __REC_DATA_PROTO_FIELDOPS__

#include "rec/data/Value.h"

namespace rec {
namespace data {

class Address;
class ValueProto;

string copyFrom(const Address& a, Message* m, const Value& value);
string copyTo(const Address& a, const Message& m, ValueProto* value);

Value getValueWithAddress(const Address&, const Message&);
void setValueWithAddress(const Address&, Message*, const ValueProto&);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_FIELDOPS__
