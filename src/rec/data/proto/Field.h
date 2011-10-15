#ifndef __REC_PROTO_FIELD__
#define __REC_PROTO_FIELD__

#include "rec/data/Editable.h"
#include "rec/data/Address.h"
#include "rec/data/proto/MessageField.h"

namespace rec {
namespace data {

class Field : public MessageField {
 public:
  static Field* makeField(const Address& address, const Message& msg);

  bool dereference(const Address::Part& part);
  bool apply(const Operation& op);
  bool undo(const Operation& op, Operation* undo);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_FIELD__
