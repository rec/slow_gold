#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

UntypedDataListener::UntypedDataListener(const string& tn, Scope scope)
    : typeName_(tn), data_(NULL) {
  if (scope == GLOBAL_SCOPE) {
    setData(global());
  } else {
    setData(empty());
    data::getData<VirtualFile>(global())->addListener(this);
  }
}

void UntypedDataListener::operator()(const VirtualFile& vf) {
  Lock l(lock_);
  setData(file::empty(vf) ? &vf : empty());
}

void UntypedDataListener::setData(const VirtualFile* vf) {
  Data* newData = data::getData(typeName_, vf);

  Lock l(lock_);

  if (data_)
    data_->removeListener(this);

  if ((data_ = newData))
    data_->addListener(this);
}

Data* UntypedDataListener::getData() const {
  Lock l(lock_);
  return data_;
}


}  // namespace data
}  // namespace rec
