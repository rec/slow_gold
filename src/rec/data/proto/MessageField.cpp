#include <google/protobuf/message.h>

#include "rec/data/proto/MessageField.h"

namespace rec {
namespace proto {

bool MessageField::hasValue() const {
  return message_->GetReflection()->HasField(*message_, field_);
}

int MessageField::getSize() const {
  return message_->GetReflection()->FieldSize(*message_, field_);
}

}  // namespace proto
}  // namespace rec
