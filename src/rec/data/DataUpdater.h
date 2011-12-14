#ifndef __REC_DATA_PERSIST_EDITABLEUPDATER__
#define __REC_DATA_PERSIST_EDITABLEUPDATER__

#include "rec/data/NewData.h"
#include "rec/data/UndoQueue.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace data {

class DataRegistry;
class UndoQueue;
class Data;

class DataUpdater {
 private:
  DataUpdater(DefaultRegistry*, DataRegistry*);
  ~DataUpdater();

 public:
  // A piece of data got new information!
  void needsUpdate(Data*);
  bool update();
  bool write();

  UndoQueue* undoQueue() { return &undoQueue_; }
  Data* getData(const string& typeName, const VirtualFile* vf);

  const DefaultRegistry& defaultRegistry() { return *defaultRegistry_; }
  DataRegistry* dataRegistry() const { return dataRegistry_.get(); }

 private:
  CriticalSection lock_;

  typedef std::map<string, Data*> DataMap;
  typedef std::set<string, Data*> DataSet;

  DataMap map_;
  UndoQueue undoQueue_;
  ptr<DefaultRegistry> defaultRegistry_;
  ptr<data::DataRegistry> dataRegistry_;

  DataSet updateData_;
  DataSet writeData_;
  thread_ptr<Thread> updateThread_;
  thread_ptr<Thread> writeThread_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataUpdater);


  static DataUpdater* instance() { return instance_; }
  static void start(DefaultRegistry*, DataRegistry*);
  static void stop();
  const CriticalSection& lock() { return lock_; }

 private:
  static DataUpdater* instance_;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_EDITABLEUPDATER__
