#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

struct UntypedDataListener::FileListener : public Listener<const Message&> {
  FileListener(UntypedDataListener* parent) : parent_(parent) {}

  virtual void operator()(const Message& m) {
    if (const VirtualFile* vf = dynamic_cast<const VirtualFile*>(&m))
      parent_->setData(file::empty(*vf) ? noData() : vf);
    else
      LOG(DFATAL) << "Got the wrong update for the file listener";
  }

  UntypedDataListener* const parent_;
};


UntypedDataListener::UntypedDataListener(const string& tn, Scope scope)
    : typeName_(tn), data_(NULL), fileListener_(new FileListener(this)),
      started_(false) {
}

UntypedDataListener::~UntypedDataListener() {
  DCHECK(started_) << "created a listener but never started it! "
                   << typeName();
}

void UntypedDataListener::startListening(Scope scope) {
  Lock l(lock_);
  if (started_) {
    LOG(DFATAL) << "Can't start a listener twice";
  } else if (scope == GLOBAL_SCOPE) {
    setData(global());
  } else {
    setData(noData());
    data::getData<VirtualFile>(global())->addListener(fileListener_.get());
  }

  started_ = true;
}

void UntypedDataListener::setData(const VirtualFile* vf) {
  Lock l(lock_);
  Data* newData = data::getData(typeName_, vf);

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
