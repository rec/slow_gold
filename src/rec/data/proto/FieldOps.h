#ifndef __REC_DATA_PROTO_FIELDOPS__
#define __REC_DATA_PROTO_FIELDOPS__

#include "rec/data/Value.h"

namespace rec {
namespace data {

class Address;
class ValueProto;

// Get or set a field in a Messsage and return a string error.
string getMessageField(const Address& a, const Message& m, ValueProto* value);
string setMessageField(const Address& a, Message* m, const ValueProto& value);

// Get or set a field in a Message, logging DFATAL if there's an error.
Value getMessageFieldOrDie(const Address&, const Message&);
void setMessageFieldOrDie(const Address&, Message*, const ValueProto&);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_FIELDOPS__
