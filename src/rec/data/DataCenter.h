#ifndef __REC_DATA_DATACENTER__
#define __REC_DATA_DATACENTER__

#include "rec/data/proto/Address.pb.h"
#include "rec/util/proto/Proto.h"

namespace rec {

namespace util { class MessageMaker; }
namespace util { class MessageRegistrar; }
namespace util { class MessageRegistrarAndMaker; }

namespace data {

class DataMaker;
class DataMap;
class DataUpdater;
class UndoStack;

class DataCenter {
 public:
  DataCenter();
  ~DataCenter();

  void clearUndoes() const;
  bool hasUpdates() const;

  UndoStack* undoStack() const { return undo_.get(); }

  void waitTillClear() const;

  MessageRegistrar* messageRegistrar();
  DataMap* dataMap() { return map_.get(); }
  DataUpdater* updater() { return updater_.get(); }
  const MessageMaker& messageMaker() const;

 private:
  unique_ptr<MessageRegistrarAndMaker> registry_;
  unique_ptr<DataUpdater> updater_;
  unique_ptr<UndoStack> undo_;
  unique_ptr<DataMaker> maker_;
  unique_ptr<DataMap> map_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataCenter);
};

DataCenter* getDataCenter();
void deleteDataCenter();

AddressProto::Scope getScope(const string& typeName);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATACENTER__
