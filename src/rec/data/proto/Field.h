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

  explicit Field(Message* message) {
    message_ = message;
    index_ = -1;
    undo_ = NULL;
    operation_ = NULL;
  }

  bool dereference(const Address::Part& part);
  Operation* applyToMessage(const Operation& op);

  bool copyFrom(const Value& value);
  bool addFrom(const Value& value);
  bool copyTo(ValueProto* value) const;

 private:
  bool addRepeated();
  bool removeRepeated();
  bool swapRepeated();

  bool clearRepeated();
  bool clearSingle();

  bool setIndexed() { return setSingle(); }
  bool setSingle();

  bool error();

  bool doRemove(int toRemove = -1);

  Operation* undo_;
  const Operation* operation_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Field);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_FIELD__
