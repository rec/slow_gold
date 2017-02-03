#pragma once

#include "rec/data/UndoStack.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace data {

class Data;
class DataMap;
class DataSet;
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
  DataMap* map_;
  std::unique_ptr<DataSet> update_;
  std::unique_ptr<DataSet> write_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataUpdater);
};

}  // namespace data
}  // namespace rec
