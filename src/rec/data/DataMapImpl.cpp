#include "rec/data/DataMapImpl.h"

#include "rec/data/DataMaker.h"
#include "rec/data/MessageMaker.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {

namespace {

const char* const EMPTY_DIRECTORY_NAME = "empty-empty-empty";

File dataFile(const VirtualFile* vf, const string& typeName) {
  File directory = vf ? getShadowDirectory(*vf) : File(EMPTY_DIRECTORY_NAME);
  return directory.getChildFile(typeName);
}

struct DataMap::DataFile {
  DataFile(Data* d, const File& f) : data_(d), file_(f) {}

  ptr<Data> data_
  File file_;
};

}  // namespace

DataMapImpl::DataMapImpl(MessageMaker* m, DataMaker* d)
    : messageMaker_(m), dataMaker_(d) {
}

virtual DataMapImpl::~DataMapImpl() {
  stl::deleteMapPointers(&map_);
}

Data* DataMap::getData(const string& typeName, const VirtualFile* vf) {
  File file = dataFile(vf, typeName);
  string key = str(file);

  Lock l(lock_);
  Map::iterator i = map_.find(key);
  if (i != map_.end())
    return i->second->first;

  ptr<Message> msg(messageMaker_->makeMessage(typeName));
  if (!msg) {
    LOG(DFATAL) << "Unable to make messages for " << typeName;
    return NULL;
  }

  ptr<Data> data(dataMaker_->makeData(msg.transfer()));
  if (!data) {
    LOG(DFATAL) << "Unable to make data for " << typeName;
    return NULL;
  }

  ptr<DataFile> df(new DataFile(data.get(), file));
  map_.insert(i, make_pair(key, df.transfer()));
  return data.transfer();
}

}  // namespace data
}  // namespace rec
