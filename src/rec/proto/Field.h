#ifndef __REC_PROTO_FIELD__
#define __REC_PROTO_FIELD__

#include "rec/base/basictypes.h"

namespace google {
namespace protobuf {

class Message;
class FieldDescriptor;

}  // namespace protobuf
}  // namespace google

namespace rec {
namespace proto {

struct Field {
  Message* message_;
  const FieldDescriptor* field_;
  uint32 index_;
  bool isIndexed_;

  explicit Field(Message* message)
      : message_(message),
        field_(NULL),
        isIndexed_(false) {
  }

  bool dereference(int32 tag) {
    if (f->field_) {
      const Reflection& r = *message_->GetReflection();
      if (isIndexed_) {
        if (field_->type() != FieldDescriptor::TYPE_MESSAGE) {
          LOG(ERROR) << "Non-terminal field had type " << field_->type();
          return false;
        }
        message_ = r.MutableRepeatedMessage(message_, field_, index_);
        isIndexed_ = false;
      } else if (isRepeated()) {
        isIndexed_ = true;
        index_ = tag;
        return true;
      } else {
        message_ = r.MutableMessage(message_, field);
      }
    }
    field_ = message_.GetDescriptor()->FindFieldByNumber(tag);
    if (!field_) {
      LOG(ERROR) << "No submessage with i=" << i << ", index=" << index;
      return false;
    }

    return true;
  }

  bool isRepeated() const {
    return !isIndexed_ && field_->label() == FieldDescriptor::LABEL_REPEATED;
  }
};


}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_FIELD__
