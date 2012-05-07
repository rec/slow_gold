#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

static const bool AUTO_UPDATE = true;

struct UntypedDataListener::FileListener : public Listener<const Message&> {
  FileListener(UntypedDataListener* parent) : parent_(parent) {}

  virtual void operator()(const Message& m) {
    if (const VirtualFile* vf = dynamic_cast<const VirtualFile*>(&m)) {
      if (parent_->setData(file::empty(*vf) ? noData() : vf) && !AUTO_UPDATE)
        parent_->updateCallback();
    } else {
      LOG(DFATAL) << "Got the wrong update for the file listener: "
                  << getTypeName(m);
    }
  }

  UntypedDataListener* const parent_;
};

UntypedDataListener::UntypedDataListener(const string& tn)
    : typeName_(tn), data_(NULL), initialized_(false) {
  fileListener_.reset(new FileListener(this));
}

UntypedDataListener::~UntypedDataListener() {
  DCHECK(initialized_) << "created a listener but never started it! "
                   << typeName();
}

void UntypedDataListener::init(Scope scope) {
  Lock l(lock_);
  if (initialized_) {
    LOG(DFATAL) << "Can't start a listener twice";
  } else if (scope == GLOBAL_SCOPE) {
    setData(global());
  } else {
    setData(noData());
    data::getData<VirtualFile>(global())->addListener(fileListener_.get());
  }

  initialized_ = true;
}

void UntypedDataListener::updateCallback() {
  Lock l(lock_);
  (*this)(*ptr<Message>(data_->clone()));
}

bool UntypedDataListener::setData(const VirtualFile* vf) {
  Data* newData = data::getData(typeName_, vf);
  Lock l(lock_);
  if (data_ == newData) {
    LOG(DFATAL) << "Got the same file twice";
  } else {
    fileName_.reset(vf ? new VirtualFile(*vf) : NULL);

    if (data_)
      data_->removeListener(this);

    data_ = newData;

    if (data_)
      data_->addListener(this);
    else
      wasCleared();
  }

  if (AUTO_UPDATE)  // || data_)
    updateCallback();

  return data_;
}

Data* UntypedDataListener::getData() const {
  Lock l(lock_);
  return data_;
}

}  // namespace data
}  // namespace rec
