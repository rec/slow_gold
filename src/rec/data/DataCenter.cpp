#include "rec/data/DataMakerImpl.h"
#include "rec/data/DataMapImpl.h"
#include "rec/data/DataUpdater.h"
#include "rec/data/MessageRegistryAndMaker.h"
#include "rec/data/UndoStack.h"

namespace rec {
namespace data {

DataCenter() : registry_(new MessageRegistryAndMaker),
               updater_(new DataUpdater),
               undo_(new UndoStack),
               maker_(new DataMakerImpl(updater_.get(), &undo_.get())),
               map_(new DataMapImpl(registry_.get(), maker_.get())) {
}

DataCenter::~DataCenter() {}

const DataCenter& getDataCenter() {
  static DataCenter dataCenter;
  return dataCenter;
}

}  // namespace data
}  // namespace rec
