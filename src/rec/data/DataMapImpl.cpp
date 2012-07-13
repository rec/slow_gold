#include "rec/data/DataMapImpl.h"

#include "rec/data/Data.h"
#include "rec/data/DataMaker.h"
#include "rec/data/MessageMaker.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace data {

namespace {

#if JUCE_WINDOWS
const char* const EMPTY_DIRECTORY_NAME = "C:\\empty-empty-empty";
#else
const char* const EMPTY_DIRECTORY_NAME = "/empty-empty-empty";
#endif

File dataFile(const VirtualFile& vf, const string& typeName) {
  return getShadowDirectory(vf).getChildFile(str(typeName));
}

}  // namespace

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

  // TODO:  we should just delete data for files that aren't in memory
  // any more.
}

void DataMapImpl::removeData(Data* data) {
    // TODO: why doesn't this work?
  if (!false)
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
