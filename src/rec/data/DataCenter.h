#pragma once

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
    std::unique_ptr<MessageRegistrarAndMaker> registry_;
    std::unique_ptr<DataUpdater> updater_;
    std::unique_ptr<UndoStack> undo_;
    std::unique_ptr<DataMaker> maker_;
    std::unique_ptr<DataMap> map_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(DataCenter);
};

DataCenter* getDataCenter();
void deleteDataCenter();

AddressProto::Scope getScope(const string& typeName);

}  // namespace data
}  // namespace rec
