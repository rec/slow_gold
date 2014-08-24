#include "rec/data/AddressListener.h"

#include "rec/data/Address.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/util/proto/MessageMaker.h"
#include "rec/data/Opener.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/util/file/FileType.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace data {

typedef AddressProto::Scope Scope;

struct AddressListener::UntypedListener : public UntypedDataListener {
  UntypedListener(AddressListener* p, const string& typeName)
      : UntypedDataListener(typeName), parent_(p) {
    DCHECK_NE(typeName, getTypeName<VirtualFile>());
  }
  AddressListener* parent_;

  virtual void operator()(const Message& m) {
    parent_->receiveMessage(m);
  }
};

AddressListener::AddressListener(const Address& a)
    : address_(a), failOnError_(true) {
  untypedListener_.reset(new UntypedListener(this, a.type_name()));
}

AddressListener::~AddressListener() {}

void AddressListener::updateCallback() {
  untypedListener_->updateCallback();
}

static void logError(const string& error, bool failOnError) {
  if (!error.empty()) {
    if (failOnError)
      LOG(DFATAL) << error;
  }
}

void AddressListener::setValue(const Value& v, Undoable undoable) const {
  Opener<Message> opener(untypedListener_->getData(), undoable);
  logError(setMessageField(address_, opener.mutable_get(), v), failOnError_);
}

const Value AddressListener::getValue(const Message& m) const {
  Value value;
  logError(getMessageField(address_, m, &value), failOnError_);
  return value;
}

const Value AddressListener::getValue() const {
  return getValue(*Opener<Message>(untypedListener_->getData(), CANT_UNDO));
}

void AddressListener::receiveMessage(const Message& m) {
  if (m.GetTypeName() == untypedListener_->typeName())
    (*this)(getValue(m));
  else
    LOG(DFATAL) << "Bad update " << m.GetTypeName() << ", " << untypedListener_->typeName();
}

}  // namespace data
}  // namespace rec
