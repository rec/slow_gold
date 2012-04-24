#include "rec/data/DataCenter.h"

#include "rec/data/DataMakerImpl.h"
#include "rec/data/DataMapImpl.h"
#include "rec/data/DataUpdater.h"
#include "rec/data/MessageRegistrarAndMaker.h"
#include "rec/data/UndoStack.h"

namespace rec {
namespace data {

DataCenter::DataCenter()
  : registry_(new MessageRegistrarAndMaker),
    updater_(new DataUpdater()),
    undo_(new UndoStack),
    maker_(new DataMakerImpl(updater_.get(), undo_.get())),
    map_(new DataMapImpl(registry_.get(), maker_.get())) {
  updater_->setMap(map_.get());
}

DataCenter::~DataCenter() {}

const CriticalSection& DataCenter::lock() const {
  return updater_->lock();
}

bool DataCenter::hasUpdates() const {
  return updater_->hasUpdates();
}

void DataCenter::clearUndoes() const {
  UndoStack* undo = const_cast<UndoStack*>(undo_.get());
  undo->clear();
}

void DataCenter::waitTillClear() const {
  while (hasUpdates())
    Thread::sleep(1);
}

static DataCenter** getDC() {
  static DataCenter* dataCenter = new DataCenter;
  return &dataCenter;
}

void deleteDataCenter() {
  delete *getDC();
  *getDC() = NULL;
}

const DataCenter& getDataCenter() {
  return **getDC();
}

}  // namespace data
}  // namespace rec
