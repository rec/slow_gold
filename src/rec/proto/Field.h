#ifndef __REC_PROTO_FIELD__
#define __REC_PROTO_FIELD__

#include "rec/base/basictypes.h"
#include "rec/proto/Proto.pb.h"

namespace google {
namespace protobuf {

class Message;
class FieldDescriptor;

}  // namespace protobuf
}  // namespace google

namespace rec {
namespace proto {

class Field {
 public:
  typedef google::protobuf::Message Message;
  typedef google::protobuf::FieldDescriptor FieldDescriptor;

  static Operation* apply(const Operation &op, 
                          Message* message);

 private:
  explicit Field(Message* message)
      : message_(message),
        field_(NULL) {
  }

  bool dereference(int32 tag);
  Operation* apply(const Operation& op);

  enum Type {
    INDEXED = 0,
    REPEATED = 1,
    SINGLE = 2,
    TYPE_COUNT = 3,
  };

  bool copyFrom(const Value& value);
  bool copyTo(Value* value) const;

  Operation* addRepeated(const Operation& op);
  Operation* removeRepeated(const Operation& op);
  Operation* swapRepeated(const Operation& op);

  Operation* clearRepeated(const Operation& op);
  Operation* clearSingle(const Operation& op);

  Operation* setIndexed(const Operation& op);
  Operation* setRepeated(const Operation& op);
  Operation* setSingle(const Operation& op);

  Operation* error(const Operation& op);

  Message* message_;
  const FieldDescriptor* field_;
  uint32 index_;
  Type type_;
};


}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_FIELD__
