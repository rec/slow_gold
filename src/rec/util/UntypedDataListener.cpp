#include "rec/util/UntypedDataListener.h"

namespace rec {
namespace util {

UntypedDataListener::UntypedDataListener(const string& typeName,
                                         const data::Address& address,
                                         bool isGlobal)
    : data_(data::emptyEditable()),
      typeName_(typeName),
      address_(address),
      isGlobal_(isGlobal) {
}

void UntypedDataListener<Proto>::requestUpdates() {
  if (isGlobal_)
    setData(getUntypedData(typeName_, address_));
  else
    data::editable<VirtualFile>()->addListener(this);
}

void UntypedDataListener<Proto>::operator()(const VirtualFile& f) {
  setData(file::empty(f) ? data::emptyEditable() :
          getUntypedData(typeName_, address_, f));
}


void UntypedDataListener<Proto>::setData(data::UntypedEditable* d) {
  Proto p;
  {
    Lock l(lock());
    data_->removeListener(this);
    data_ = d;
    data_->addListener(this);
  }
}

}  // namespace util
}  // namespace rec
