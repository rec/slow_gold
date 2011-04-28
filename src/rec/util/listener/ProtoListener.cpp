#include "rec/util/listener/ProtoListener.h"

namespace rec {
namespace util {
namespace listener {

void ProtoListener::setData(persist::UntypedData* data) {
  if (data_)
    data_->messageBroadcaster()->removeListener(this);

  data_ = data;

  if (data_) {
    data_->messageBroadcaster()->addListener(this);
    (*this)(*ptr<Message>(data_->clone()));
  }
}

}  // namespace listener
}  // namespace util
}  // namespace rec
