#include "rec/data/DataMap.h"

namespace rec {
namespace data {

const char* const EMPTY_DIRECTORY_NAME = "empty-empty-empty";

File editableFile(const string& typeName, const VirtualFile* vf) {
  return getShadowFile(vf ? *vf : file::none(), str(typeName));
}

File dataFile(const VirtualFile* vf, const string& typeName) {
  File directory = vf ? getShadowDirectory(*vf) : File(EMPTY_DIRECTORY_NAME);
  return directory.getChildFile(typeName);
}

DataMap::~DataMap() {
  stl::deleteMapPointers(&map_);
}

const DataFile* DataMap::getData(const string& typeName, const VirtualFile* vf) {
  File file = dataFile(vf, typeName);
  string key = str(file);

  Lock l(lock_);
  Map::iterator i = map_.find(key);
  if (i != map_.end())
    return i->second;

  ptr<Message> msg(messageMaker_.make(typeName));
  if (!msg) {
    LOG(DFATAL) << "Unable to make messages for " << typeName;
    return NULL;
  }

  ptr<Data> data(dataMaker_.makeData(msg.transfer()));
  if (!data) {
    LOG(DFATAL) << "Unable to make data for " << typeName;
    return NULL;
  }

  ptr<DataFile> df(new DataFile(data.transfer(), file));
  map_.insert(i, make_pair(key, df.get());
  return df.transfer();
}

}  // namespace data
}  // namespace rec
