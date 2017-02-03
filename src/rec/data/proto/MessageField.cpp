#include <google/protobuf/message.h>

#include "rec/data/proto/MessageField.h"

namespace rec {
namespace data {

bool hasValue(const MessageField& mf) {
    return mf.message_->GetReflection()->HasField(*mf.message_, mf.field_);
}

int getSize(const MessageField& mf) {
    return mf.message_->GetReflection()->FieldSize(*mf.message_, mf.field_);
}

}  // namespace data
}  // namespace rec
