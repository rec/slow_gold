#include "rec/util/listener/ProtoListener.h"
#include "rec/data/Data.h"
#include "rec/data/proto/Proto.h"

namespace rec {
namespace util {
namespace listener {

using namespace rec::data;

void ProtoListener::setData(UntypedData* data) {
  if (data_)
    data_->messageBroadcaster()->removeListener(this);

  data_ = data;

  if (data_) {
    data_->messageBroadcaster()->addListener(this);
    (*this)(*ptr<Message>(data_->clone()));
  }
}

void ProtoListener::operator()(const Message& m) {
  setDisplayValue(getValue(address_, m));
}

void ProtoListener::updatePersistentData() {
  if (data::Data* d = getData())
    data::set(d, address_, getDisplayValue());
}

}  // namespace listener
}  // namespace util
}  // namespace rec
