#include "rec/util/listener/ProtoListener.h"
#include "rec/data/Data.h"
#include "rec/data/proto/Proto.h"

namespace rec {
namespace util {
namespace listener {

using namespace rec::data;

void ProtoListener::setData(UntypedData* data) {
  if (untypedData_)
    untypedData_->messageBroadcaster()->removeListener(this);

  untypedData_ = data;

  if (untypedData_) {
    untypedData_->messageBroadcaster()->addListener(this);
    (*this)(*ptr<Message>(untypedData_->clone()));
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
