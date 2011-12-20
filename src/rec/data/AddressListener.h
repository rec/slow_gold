#ifndef __REC_DATA_ADDRESSLISTENER__
#define __REC_DATA_ADDRESSLISTENER__

#include "rec/data/Address.h"
#include "rec/data/Opener.h"
#include "rec/data/Operation.pb.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/Value.h"
#include "rec/data/proto/FieldOps.h"

namespace rec {
namespace data {

class AddressListener : public UntypedDataListener,
                        public Listener<const Value&> {
 public:
  AddressListener(const Address& a, const string& typeName,
                  Scope scope = FILE_SCOPE)
      : UntypedDataListener(typeName, scope), address_(a) {
  }
  virtual ~AddressListener() {}

  virtual void operator()(const Value&) = 0;
  virtual void operator()(const Message& m) {
    (*this)(getValue(m));
  }

  virtual void setValue(const Value& v, Undoable undoable = CAN_UNDO) const {
    Opener<Message> opener(getData(), undoable);
    setValueWithAddress(address_, opener.mutable_get(), v);
  }

  const Value getValue(const Message& m) const {
    return getValueWithAddress(address_, m);
  }

  const Value getValue() const {
    return getValue(*Opener<Message>(getData(), CANT_UNDO));
  }

 private:
  const Address address_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(AddressListener);
};

class GlobalAddressListener : public AddressListener {
 public:
  GlobalAddressListener(const Address& a, const string& tn)
      : AddressListener(a, tn) {
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GlobalAddressListener);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_ADDRESSLISTENER__
