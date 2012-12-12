#include "rec/data/DataMapImpl.h"

#include "rec/data/Data.h"
#include "rec/data/DataMaker.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/proto/MessageMaker.h"

namespace rec {
namespace data {

struct DataMapImpl::DataRecord {
  DataRecord(Data* d, const File& f) : data_(d), file_(f) {}

  Data* data_;
  File file_;
};

DataMapImpl::DataMapImpl(MessageMaker* m, DataMaker* d)
    : messageMaker_(m), dataMaker_(d) {
}

DataMapImpl::~DataMapImpl() {
  for (Map::iterator i = map_.begin(); i != map_.end(); ++i) {
    delete i->second->data_;
    delete i->second;
  }
}

Data* DataMapImpl::getData(const string& typeName, const VirtualFile& vf) {
  File file = getShadowDirectory(vf).getChildFile(str(typeName));
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

  DCHECK_EQ(typeName, getTypeName(*msg));
  bool isEmpty = (vf.type() == VirtualFile::NONE);
  Data* data = dataMaker_->makeData(msg.transfer(), file, isEmpty, key);
  if (!data) {
    LOG(DFATAL) << "Unable to make data for " << typeName;
    return NULL;
  }

  DataRecord* df = new DataRecord(data, file);
  map_.insert(i, make_pair(key, df));
  return data;
}

void DataMapImpl::updateAll() {
  Lock l(lock_);
  for (Map::iterator i = map_.begin(); i != map_.end(); ++i)
    i->second->data_->update();
}

static bool ENABLE_DELETIONS = false;

void DataMapImpl::removeData(Data* data) {
  if (!ENABLE_DELETIONS)
    return;

  Lock l(lock_);
  const string& key = data->key();
  Map::iterator i = map_.find(key);
  if (i != map_.end()) {
    map_.erase(i);
    delete data;
  } else {
    LOG(DFATAL) << "Tried to remove a non-existent piece of data";
  }
}



}  // namespace data
}  // namespace rec
