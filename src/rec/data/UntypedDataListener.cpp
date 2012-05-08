#include "rec/data/UntypedDataListener.h"

#include "rec/data/DataOps.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

namespace {

Broadcaster<DataFile>* fileListener() {
  static Broadcaster<DataFile> listener;
  return &listener;
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
  (*this)(*msg);
}

void UntypedDataListener::setGlobalDataFile(DataFile datafile) {
  fileListener()->broadcast(datafile);
}

}  // namespace data
}  // namespace rec
