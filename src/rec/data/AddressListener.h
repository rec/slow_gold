#ifndef __REC_DATA_ADDRESSLISTENER__
#define __REC_DATA_ADDRESSLISTENER__

#include "rec/data/Address.h"
#include "rec/data/Opener.h"
#include "rec/data/Value.h"
#include "rec/util/Listener.h"

namespace rec {
namespace data {

class Address;

class AddressListener : public Listener<const Value&> {
 public:
  AddressListener(const Address& a, const string& typeName,
                  Scope scope = FILE_SCOPE);
  virtual ~AddressListener();

  virtual void operator()(const Value&) = 0;

  virtual void setValue(const Value& v, Undoable undoable = CAN_UNDO) const;
  const Value getValue(const Message& m) const;
  const Value getValue() const;
  const Address& address() const { return address_; }

  void setFailOnError(bool f) { failOnError_ = f; }
  void updateCallback();

 private:
  struct UntypedListener;

  void receiveMessage(const Message&);

  ptr<UntypedListener> untypedListener_;
  const Address address_;
  bool failOnError_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(AddressListener);
};

class GlobalAddressListener : public AddressListener {
 public:
  GlobalAddressListener(const Address& a, const string& typeName)
      : AddressListener(a, typeName, GLOBAL_SCOPE) {
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GlobalAddressListener);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_ADDRESSLISTENER__
