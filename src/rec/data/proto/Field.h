#ifndef __REC_PROTO_FIELD__
#define __REC_PROTO_FIELD__

#include "rec/base/base.h"

namespace rec {
namespace data {

class Address;
class MessageField;

bool fillMessageField(MessageField*, const Address&, const Message&);

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_FIELD__
