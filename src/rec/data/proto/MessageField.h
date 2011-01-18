#ifndef __REC_DATA_PROTO_MESSAGEFIELD__
#define __REC_DATA_PROTO_MESSAGEFIELD__

#include "rec/base/base.h"

namespace google {
namespace protobuf {

class FieldDescriptor;

}  // namespace protobuf
}  // namespace google

using google::protobuf::FieldDescriptor;

namespace rec {
namespace proto {

struct MessageField {
  MessageField() {}
  MessageField(Message* m, const FieldDescriptor* f = NULL)
      : message_(m), field_(f) {
  }

  bool hasValue() const;
  int getSize() const;

  Message* message_;
  const FieldDescriptor* field_;
};

}  // namespace proto
}  // namespace rec

#endif  // __REC_DATA_PROTO_MESSAGEFIELD__
