#ifndef __REC_DATA_DATACENTER__
#define __REC_DATA_DATACENTER__

#include "rec/base/base.h"

namespace rec {
namespace data {

class DataMaker;
class DataMap;
class DataUpdater;
class MessageRegistrarAndMaker;
class UndoStack;

struct DataCenter {
  DataCenter();
  ~DataCenter();

  ptr<MessageRegistrarAndMaker> registry_;
  ptr<DataUpdater> updater_;
  ptr<UndoStack> undo_;
  ptr<DataMaker> maker_;
  ptr<DataMap> map_;

  bool hasUpdates() const;
  const CriticalSection& lock() const;
};

const DataCenter& getDataCenter();
void deleteDataCenter();

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATACENTER__
