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

// DataUpdater sends out updates to data clients and writes copies of the data
// to the file system.
class DataUpdater {
 private:
  DataUpdater() : updateThread_(NULL), writeThread_(NULL) {}
  ~DataUpdater() {}

  void needsUpdate(Data*);
  bool update();
  bool write();

 private:
  CriticalSection lock_;

  Thread* updateThread_;
  Thread* writeThread_;

  typedef std::set<string, Data*> DataSet;

  DataSet updateData_;
  DataSet writeData_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataUpdater);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_EDITABLEUPDATER__
