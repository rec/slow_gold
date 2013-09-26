#include "rec/data/DataCenter.h"

#include "rec/util/StateListener.h"
#include "rec/data/DataMakerImpl.h"
#include "rec/data/DataMapImpl.h"
#include "rec/data/DataUpdater.h"
#include "rec/data/UndoStack.h"
#include "rec/util/proto/MessageRegistrarAndMaker.h"

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

DataCenter::~DataCenter() {
  StateBroadcaster::instance()->clear();
}

bool DataCenter::hasUpdates() const {
  return updater_->hasUpdates();
}

void DataCenter::clearUndoes() const {
  // TODO: get rid of this const_cast
  UndoStack* undo = const_cast<UndoStack*>(undo_.get());
  undo->clear();
}

void DataCenter::waitTillClear() const {
  // When this was a while loop, it sometimes looped forever...!
  if (hasUpdates())
    Thread::sleep(10);
}

MessageRegistrar* DataCenter::messageRegistrar() {
  return registry_.get();
}

const MessageMaker& DataCenter::messageMaker() const {
  return *registry_;
}

static DataCenter** getDC() {
  static DataCenter* dataCenter = new DataCenter;
  return &dataCenter;
}

void deleteDataCenter() {
  delete *getDC();
  *getDC() = nullptr;
}

DataCenter* getDataCenter() {
  return *getDC();
}

AddressProto::Scope getScope(const string& typeName) {
  return getDataCenter()->messageMaker().getScope(typeName);
}

}  // namespace data
}  // namespace rec
