#include "rec/util/UntypedDataListener.h"
#include "rec/data/Data.h"
#include "rec/data/DataRegistry.h"
#include "rec/data/EditableUpdater.h"

namespace rec {
namespace util {

using namespace rec::data;

UntypedDataListener::UntypedDataListener(const string& typeName,
                                         const data::Address& address,
                                         bool isGlobal)
    : data_(data::editable(typeName, NULL)),
      typeName_(typeName),
      address_(address),
      isGlobal_(isGlobal) {
}

void UntypedDataListener::requestUpdates() {
  if (isGlobal_)
    setData(data::editable(typeName_, &file::none()));
  else
    data::editable<VirtualFile>()->addListener(this);
}

void UntypedDataListener::operator()(const VirtualFile& f) {
  setData(data::editable(typeName_, file::empty(f) ? NULL : &f));
}

void UntypedDataListener::setData(data::UntypedEditable* d) {
  {
    Lock l(lock_);
    data_->broadcaster()->removeListener(this);
    data_ = d;
    data_->broadcaster()->addListener(this);
  }
  (*this)(*ptr<Message>(d->clone()));
}

}  // namespace util
}  // namespace rec
