#include "rec/data/DataMapImpl.h"

#include "rec/data/Data.h"
#include "rec/data/DataMaker.h"
#include "rec/data/MessageMaker.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

namespace {

const char* const EMPTY_DIRECTORY_NAME = "/empty-empty-empty";

File dataFile(const VirtualFile* vf, const string& typeName) {
  File directory = vf ? getShadowDirectory(*vf) : File(EMPTY_DIRECTORY_NAME);
  return directory.getChildFile(str(typeName));
}

}  // namespace

struct DataMapImpl::DataFile {
  DataFile(Data* d, const File& f) : data_(d), file_(f) {}

  Data* data_;
  File file_;
};

DataMapImpl::DataMapImpl(MessageMaker* m, DataMaker* d)
    : messageMaker_(m), dataMaker_(d) {
}

DataMapImpl::~DataMapImpl() {
  DLOG(INFO) << "Deleting DataMapImpl";
  for (Map::iterator i = map_.begin(); i != map_.end(); ++i) {
    delete i->second->data_;
    delete i->second;
  }
}

Data* DataMapImpl::getData(const string& typeName, const VirtualFile* vf) {
  File file = dataFile(vf, typeName);
  string key = str(file);

  Lock l(lock_);
  Map::iterator i = map_.find(key);
  if (i != map_.end())
    return i->second->data_;

  ptr<Message> msg(messageMaker_->makeMessage(typeName));
  if (!msg) {
    LOG(DFATAL) << "Unable to make messages for " << typeName;
    return NULL;
  }

  Data* data = dataMaker_->makeData(msg.transfer(), file);
  if (!data) {
    LOG(DFATAL) << "Unable to make data for " << typeName;
    return NULL;
  }

  DataFile* df = new DataFile(data, file);
  map_.insert(i, make_pair(key, df));
  return data;
}

}  // namespace data
}  // namespace rec
