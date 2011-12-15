#include "rec/data/DataMap.h"

#include "rec/data/Data.h"
#include "rec/data/MessageMaker.h"
#include "rec/util/file/VirtualFile.pbh"
#include "rec/util/Stl.h"

namespace rec {
namespace data {
namespace {

class DataImpl : public Data {
 public:
  DataImpl(Message *m, UndoStack* queue, DataUpdater* updater)
      : Data(m),
        undoStack_(queue),
        dataUpdater_(updater) {
  }

 private:
  virtual void addToUndoStack(const Message& before) {
    undo.addToUndoStack(this, before, *message_);
  }
  virtual void reportChange() const {

  }

  UndoStack* undoStack_;
  DataUpdater* dataUpdater_;
};

class DataMapImpl : public DataMap {
 public:
  DataMapImpl() {}

  virtual ~DataMapImpl() {
    stl::deleteMapPointers(&map_);
  }

  const Data* getData(const string& typeName, const VirtualFile* vf) {
    File file = dataFile(vf, typeName);
    string key = str(file);

    Lock l(lock_);
    Map::iterator i = map_.find(key);
    if (i != map_.end())
      return i->second->first;

    ptr<Message> msg(messageMaker_.makeMessage(typeName));
    if (!msg) {
      LOG(DFATAL) << "Unable to make messages for " << typeName;
      return NULL;
    }

    ptr<Data> data(makeData(msg.transfer()));
    if (!data) {
      LOG(DFATAL) << "Unable to make data for " << typeName;
      return NULL;
    }

    ptr<DataFile> df(new DataFile(data.get(), file));
    map_.insert(i, make_pair(key, df.transfer()));
    return data.transfer();
  }

  struct DataFile {
    DataFile(Data* d, const File& f) : data_(d), file_(f) {}

    ptr<Data> data_
    File file_;
  };

  typedef std::map<string, DataFile*> Map;

  CriticalSection lock_;
  Map map_;
  MessageMaker messageMaker_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataMapImpl);
};


DataMapImpl* getDataMapImpl() {
  static DataMapImpl map;
  return *map;
}

static const char* const EMPTY_DIRECTORY_NAME = "empty-empty-empty";

static File dataFile(const VirtualFile* vf, const string& typeName) {
  File directory = vf ? getShadowDirectory(*vf) : File(EMPTY_DIRECTORY_NAME);
  return directory.getChildFile(typeName);
}
}  // namespace

MessageMaker* getMessageMaker() {
  return &getDataMapImpl()->messageMaker_;
}

DataMap* getDataMap() {
  static DataMapImpl map;
  return *map;
}


}  // namespace data
}  // namespace rec
