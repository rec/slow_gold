#ifndef __REC_DATA_DATACENTER__
#define __REC_DATA_DATACENTER__

#include "rec/base/base.h"

namespace rec {

namespace util { class MessageMaker; }
namespace util { class MessageRegistrar; }
namespace util { class MessageRegistrarAndMaker; }

namespace data {

class DataMaker;
class DataMap;
class DataUpdater;
class UndoStack;

struct DataCenter {
  DataCenter();
  ~DataCenter();

  ptr<MessageRegistrarAndMaker> registry_;
  ptr<DataUpdater> updater_;
  ptr<UndoStack> undo_;
  ptr<DataMaker> maker_;
  ptr<DataMap> map_;

  void clearUndoes() const;
  bool hasUpdates() const;

  UndoStack* undoStack() const { return undo_.get(); }

  void waitTillClear() const;

  const MessageRegistrar& getMessageRegistrar() const;
  const MessageMaker& getMessageMaker() const;
};

const DataCenter& getDataCenter();
void deleteDataCenter();

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATACENTER__
