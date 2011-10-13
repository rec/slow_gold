#include "rec/util/listener/ProtoListener.h"

#include "rec/data/Editable.h"
#include "rec/data/proto/Proto.h"

namespace rec {
namespace util {
namespace listener {

using namespace rec::data;

void ProtoListener::setUntypedEditable(UntypedEditable* data) {
  if (untypedData_)
    untypedData_->messageBroadcaster()->removeListener(this);

  untypedData_ = data;

  if (untypedData_) {
    untypedData_->messageBroadcaster()->addListener(this);
    (*this)(*ptr<Message>(untypedData_->clone()));
  }
}

void ProtoListener::operator()(const Message& m) {
  setDisplayValue(untypedData_->getValue(address_));
}

void ProtoListener::updatePersistentData() {
  if (data::Editable* d = getUntypedEditable())
    d->set(getDisplayValue(), address_);
}

}  // namespace listener
}  // namespace util
}  // namespace rec
