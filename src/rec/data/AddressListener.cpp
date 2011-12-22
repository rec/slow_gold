#include "rec/data/AddressListener.h"

#include "rec/data/Address.h"
#include "rec/data/DataOps.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/FieldOps.h"

namespace rec {
namespace data {

struct AddressListener::UntypedListener : public UntypedDataListener {
  UntypedListener(AddressListener* parent, const string& typeName, Scope scope)
      : UntypedDataListener(typeName, scope), parent_(parent) {
    DCHECK_NE(typeName, getTypeName<VirtualFile>());
  }
  AddressListener* parent_;

  virtual void operator()(const Message& m) {
    parent_->setMessage(m);
  }
};

AddressListener::AddressListener(const Address& a, const string& tn, Scope s)
    : untypedListener_(new UntypedListener(this, tn, s)), address_(a) {
}

AddressListener::~AddressListener() {}

void AddressListener::setValue(const Value& v, Undoable undoable) const {
  Opener<Message> opener(untypedListener_->getData(), undoable);
  setValueWithAddress(address_, opener.mutable_get(), v);
}

const Value AddressListener::getValue(const Message& m) const {
  return getValueWithAddress(address_, m);
}

const Value AddressListener::getValue() const {
  return getValue(*Opener<Message>(untypedListener_->getData(), CANT_UNDO));
}

void AddressListener::setMessage(const Message& m) {
  if (getTypeName(m) == untypedListener_->typeName())
    (*this)(getValue(m));
  else
    LOG(ERROR) << "Bad update " << getTypeName(m) << ", " << untypedListener_->typeName();
  // TODO: should be DFATAL.
}

}  // namespace data
}  // namespace rec
