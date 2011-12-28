#include "rec/data/AddressListener.h"

#include "rec/data/Address.h"
#include "rec/data/DataOps.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/FieldOps.h"

namespace rec {
namespace data {

struct AddressListener::UntypedListener : public UntypedDataListener {
  UntypedListener(AddressListener* p, const string& typeName)
      : UntypedDataListener(typeName), parent_(p) {
    DCHECK_NE(typeName, getTypeName<VirtualFile>());
  }
  AddressListener* parent_;

  virtual void operator()(const Message& m) {
    parent_->setMessage(m);
  }
};

AddressListener::AddressListener(const Address& a, const string& tn)
    : untypedListener_(new UntypedListener(this, tn)),
      address_(a),
      failOnError_(false) {
}

AddressListener::~AddressListener() {}

void AddressListener::startListening(Scope s) {
  untypedListener_->startListening(s);
}

static void logError(const string& error, bool failOnError) {
  if (!error.empty()) {
    if (failOnError)
      LOG(DFATAL) << error;
    else
      LOG(ERROR) << error;
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

void AddressListener::setMessage(const Message& m) {
  if (getTypeName(m) == untypedListener_->typeName())
    (*this)(getValue(m));
  else
    LOG(DFATAL) << "Bad update " << getTypeName(m) << ", " << untypedListener_->typeName();
}

}  // namespace data
}  // namespace rec
