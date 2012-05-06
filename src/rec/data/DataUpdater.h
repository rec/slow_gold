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
  DataUpdater();
  ~DataUpdater();

  void reportChange(Data*);
  bool update();
  bool write();
  void setMap(DataMap* m) { map_ = m; }

  bool hasUpdates() const;

 private:
  class DataSet;
  DataMap* map_;
  ptr<DataSet> update_;
  ptr<DataSet> write_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataUpdater);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_EDITABLEUPDATER__
