#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

struct UntypedDataListener::FileListener : public Listener<const Message&> {
  FileListener(UntypedDataListener* parent) : parent_(parent) {}

  virtual void operator()(const Message& m) {
    if (const VirtualFile* vf = dynamic_cast<const VirtualFile*>(&m))
      {
      // DLOG(INFO) << toString(*(file::empty(*vf) ? vf : empty()));
      DLOG(INFO) << toString(*vf);
      parent_->setData(file::empty(*vf) ? vf : empty());
      }
    else
      LOG(DFATAL) << "Got the wrong update for the file listener";
  }

  UntypedDataListener* const parent_;
};


UntypedDataListener::UntypedDataListener(const string& tn, Scope scope)
    : typeName_(tn), data_(NULL), fileListener_(new FileListener(this)) {
  if (scope == GLOBAL_SCOPE) {
    setData(global());
  } else {
    setData(empty());
    data::getData<VirtualFile>(global())->addListener(fileListener_.get());
  }
}

UntypedDataListener::~UntypedDataListener() {}

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
