#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace data {

namespace {

struct FileBroadcaster {
  Broadcaster<const VirtualFile&> listener_;
  VirtualFile file_;
};

FileBroadcaster* fileBroadcaster() {
  static FileBroadcaster fb;
  return &fb;
}

Broadcaster<const VirtualFile&>* fileListener() {
  return &(fileBroadcaster()->listener_);
}

}  // namespace

UntypedDataListener::UntypedDataListener(const string& tn)
    : scope_(getScope(tn)), typeName_(tn), data_(nullptr) {
  fileListener()->addListener(this);
}

UntypedDataListener::~UntypedDataListener() {}

void UntypedDataListener::operator()(const VirtualFile& df) {
  VirtualFile datafile = df;
  if (scope_ == AddressProto::GLOBAL_SCOPE) {
    if (data_)
      return;
    datafile = data::global();
  }
  Data* newData = data::getData(typeName_, datafile);
  std::unique_ptr<Message> msg;
  {
    Lock l(lock_);
    if (data_ == newData) {
      // LOG(ERROR) << "Got the same file twice " << file::toString(datafile);
      return;
    }
    if (data_)
      data_->removeListener(this);

    data_ = newData;
    data_->addListener(this);
    msg.reset(data_->clone());
  }

  fileBroadcaster()->file_ = datafile;
  (*this)(*msg);
}

void UntypedDataListener::setGlobalDataFile(const VirtualFile& datafile) {
  MessageManagerLock l;
  fileListener()->broadcast(datafile);
}

void UntypedDataListener::updateCallback() {
  std::unique_ptr<Message> m;
  {
    Lock l(lock_);
    if (!data_) {
      (*this)(fileBroadcaster()->file_);
      DCHECK(data_);
      return;
    }
    m.reset(data_->clone());
  }
  (*this)(*m);
}

}  // namespace data
}  // namespace rec
