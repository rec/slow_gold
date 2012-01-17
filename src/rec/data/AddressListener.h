#ifndef __REC_DATA_ADDRESSLISTENER__
#define __REC_DATA_ADDRESSLISTENER__

#include "rec/data/Address.h"
#include "rec/data/Opener.h"
#include "rec/data/Value.h"
#include "rec/util/Listener.h"

namespace rec {
namespace data {

class Address;
class UntypedDataListener;

class AddressListener : public Listener<const Value&> {
 public:
  AddressListener(const Address& a, const string& typeName);
  virtual ~AddressListener();
  virtual void startListening() { startListening(FILE_SCOPE); }

  void startListening(Scope s);

  virtual void operator()(const Value&) = 0;

  virtual void setValue(const Value& v, Undoable undoable = CAN_UNDO) const;
  const Value getValue(const Message& m) const;
  const Value getValue() const;
  const Address& address() const { return address_; }
  bool isStarted() const;

  void setFailOnError(bool f) { failOnError_ = f; }

 private:
  struct UntypedListener;
  friend struct UntypedListener;

  void receiveMessage(const Message&);

  ptr<UntypedListener> untypedListener_;
  const Address address_;
  bool failOnError_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(AddressListener);
};

class GlobalAddressListener : public AddressListener {
 public:
  GlobalAddressListener(const Address& a, const string& tn)
      : AddressListener(a, tn) {
  }

  virtual void startListening() {
    AddressListener::startListening(GLOBAL_SCOPE);
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GlobalAddressListener);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_ADDRESSLISTENER__
