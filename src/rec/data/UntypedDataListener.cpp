#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

namespace {

struct FileBroadcaster {
  Broadcaster<DataFile> listener_;
  ptr<VirtualFile> file_;
};

FileBroadcaster* fileBroadcaster() {
  static FileBroadcaster fb;
  return &fb;
}

Broadcaster<DataFile>* fileListener() {
  return &(fileBroadcaster()->listener_);
}

}  // namespace

UntypedDataListener::UntypedDataListener(const string& tn, Scope scope)
    : scope_(scope), typeName_(tn), data_(NULL) {
  fileListener()->addListener(this);
}

UntypedDataListener::~UntypedDataListener() {}

void UntypedDataListener::operator()(DataFile datafile) {
  if (scope_ == GLOBAL_SCOPE) {
    if (data_)
      return;
    datafile = data::global();
  }
  Data* newData = data::getData(typeName_, datafile);
  ptr<Message> msg;
  {
    Lock l(lock_);
    if (data_ == newData) {
      LOG(ERROR) << "Got the same file twice " << file::toString(datafile);
      return;
    }
    if (data_)
      data_->removeListener(this);

    data_ = newData;
    data_->addListener(this);
    msg.reset(data_->clone());
  }

  fileBroadcaster()->file_.reset(datafile ? new VirtualFile(*datafile) : NULL);
  (*this)(*msg);
}

void UntypedDataListener::setGlobalDataFile(DataFile datafile) {
  fileListener()->broadcast(datafile);
}

void UntypedDataListener::updateCallback() {
  ptr<Message> m;
  {
    Lock l(lock_);
    if (!data_) {
      (*this)(fileBroadcaster()->file_.get());
      DCHECK(data_);
      return;
    }
    m.reset(data_->clone());
  }
  (*this)(*m);
}

}  // namespace data
}  // namespace rec
