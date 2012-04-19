#ifndef __REC_DATA_PERSIST_EDITABLEUPDATER__
#define __REC_DATA_PERSIST_EDITABLEUPDATER__

#include "rec/data/UndoStack.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace data {

class Data;
class DataMap;
class UndoStack;

// DataUpdater sends out updates to data clients and writes copies of the data
// to the file system.
class DataUpdater {
 public:
  DataUpdater() : updateThread_(NULL), writeThread_(NULL), map_(NULL) {}
  ~DataUpdater() {}

  void reportChange(Data*);
  bool update();
  bool write();
  void setMap(DataMap* m) { map_ = m; }

  const CriticalSection& lock() const { return lock_; }

 private:
  CriticalSection lock_;
  CriticalSection updateLock_;
  CriticalSection writeLock_;

  Thread* updateThread_;
  Thread* writeThread_;

  typedef std::set<Data*> DataSet;

  DataSet updateData_;
  DataSet writeData_;
  DataMap* map_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataUpdater);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_EDITABLEUPDATER__
