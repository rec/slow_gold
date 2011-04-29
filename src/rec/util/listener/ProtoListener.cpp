#include "rec/util/listener/ProtoListener.h"
#include "rec/data/proto/Proto.h"

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

void ProtoListener::operator()(const Message& m) {
  setDisplayValue(proto::getValue(address_, m));
}

void ProtoListener::updatePersistentData() {
  if (getData())
    getData()->set(address_, getDisplayValue());
}

}  // namespace listener
}  // namespace util
}  // namespace rec
