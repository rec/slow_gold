#include "rec/data/AddressListener.h"

#include "rec/data/Address.h"
#include "rec/data/DataOps.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/FieldOps.h"

namespace rec {
namespace data {

struct AddressListener::UntypedListener : public UntypedDataListener {
  UntypedListener(AddressListener* p, const string& typeName, Scope s)
      : UntypedDataListener(typeName, s), parent_(p) {
    DCHECK_NE(typeName, getTypeName<VirtualFile>());
  }
  AddressListener* parent_;

  virtual void operator()(const Message& m) {
    parent_->setMessage(m);
  }
};

AddressListener::AddressListener(const Address& a, const string& tn, Scope s)
    : untypedListener_(new UntypedListener(this, tn, s)),
      address_(a),
      failOnError_(true) {
}

AddressListener::~AddressListener() {}

void AddressListener::setValue(const Value& v, Undoable undoable) const {
  Opener<Message> opener(untypedListener_->getData(), undoable);
  string error = setMessageField(address_, opener.mutable_get(), v);
  if (failOnError_ && !error.empty())
    LOG(DFATAL) << error;
}

const Value AddressListener::getValue(const Message& m) const {
  Value value;
  string error = getMessageField(address_, m, &value);
  if (failOnError_ && !error.empty())
    LOG(DFATAL) << error;
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
