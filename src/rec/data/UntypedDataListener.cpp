#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

static const bool AUTO_UPDATE = true;

struct UntypedDataListener::FileListener : public Listener<const Message&> {
  FileListener(UntypedDataListener* parent) : parent_(parent) {}
  virtual void operator()(const Message& m) { parent_->setData(m); }
  UntypedDataListener* const parent_;
};

UntypedDataListener::UntypedDataListener(const string& tn)
    : typeName_(tn), data_(NULL), initialized_(false) {
}

UntypedDataListener::~UntypedDataListener() {
  DCHECK(initialized_) << "never started listener for " << typeName();
}

void UntypedDataListener::init(Scope scope) {
  Lock l(lock_);
  if (initialized_) {
    LOG(DFATAL) << "Can't start a listener twice";
  } else if (scope == GLOBAL_SCOPE) {
    setData(global());
  } else {
    if (!fileListener_)
      fileListener_.reset(new FileListener(this));
    data::getData<VirtualFile>(global())->addListener(fileListener_.get());
  }

  initialized_ = true;
}

void UntypedDataListener::updateCallback() {
  Lock l(lock_);
  ptr<Message> msg(data_->clone());
  // DLOG(INFO) << getTypeName(*msg) << ": " << msg->ShortDebugString();
  (*this)(*msg);
}

void UntypedDataListener::setData(const Message& m) {
  if (const VirtualFile* vf = dynamic_cast<const VirtualFile*>(&m))
    setData(vf);
  else
    LOG(DFATAL) << "Got wrong update for FileListener: " << getTypeName(m);
}

void UntypedDataListener::setData(const VirtualFile* vf) {
  Data* newData = data::getData(typeName_, vf);
  Lock l(lock_);
  if (data_ == newData) {
    LOG(ERROR) << "Got the same file twice";
  } else {
    fileName_.reset(vf ? new VirtualFile(*vf) : NULL);

    if (data_)
      data_->removeListener(this);

    data_ = newData;

    if (data_)
      data_->addListener(this);
    else
      wasCleared();

    updateCallback();
  }
}

Data* UntypedDataListener::getData() const {
  Lock l(lock_);
  return data_;
}

}  // namespace data
}  // namespace rec
