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
namespace data {

struct MessageField {
  enum Type {
    INDEXED = 0,
    REPEATED = 1,
    SINGLE = 2,
    TYPE_COUNT = 3,
  };

  Message* message_;
  const FieldDescriptor* field_;

  int32 index_;
  Type type_;
  int32 repeatCount_;

  bool hasValue() const;
  int getSize() const;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_MESSAGEFIELD__
