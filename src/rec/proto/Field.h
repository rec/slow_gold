#ifndef __REC_PROTO_FIELD__
#define __REC_PROTO_FIELD__

#include "rec/base/basictypes.h"
#include "rec/base/scoped_ptr.h"
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
  bool addFrom(const Value& value);
  bool copyTo(Value* value) const;

  bool addRepeated();
  bool removeRepeated();
  bool swapRepeated();

  bool clearRepeated();
  bool clearSingle();

  bool setIndexed() { return setSingle(); }
  bool setSingle();

  bool error();

  bool doRemove(int toRemove = -1);

  Message* message_;
  const FieldDescriptor* field_;
  uint32 index_;
  Type type_;
  uint32 repeatCount_;

  Operation* undo_;
  const Operation* operation_;
};


}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_FIELD__
