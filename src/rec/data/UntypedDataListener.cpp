#include "rec/data/UntypedDataListener.h"

namespace rec {
namespace data {

UntypedDataListener::UntypedDataListener(const string& tn, bool isGlobal)
    : typeName_(tn), isGlobal_(isGlobal) {
  if (isGlobal_)
    setData(file::getData(tn, &file::none()));
  else
    (*this)(file::none());
}

UntypedDataListener::~UntypedDataListener() {}

void UntypedDataListener::operator()(const VirtualFile& vf) {
  Lock l(lock_);

  if (isGlobal_)
    LOG(DFATAL) << "Shouldn't get file updates for global data!";
  else
    setData(file::getData(typeName_, vf.file_size() ? &vf : NULL));
}

void UntypedDataListener::setData(Data* b) {
  Lock l(lock_);

  if (data_)
    data_->removeListener(this);

  if ((data_ = b))
    data_->addListener(this);
}

Data* UntypedDataListener::getData() {
  Lock l(lock_);

  return data_;
}


}  // namespace data
}  // namespace rec
