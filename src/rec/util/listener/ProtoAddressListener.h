#ifndef __REC_UTIL_LISTENER_UNTYPEDADDRESSLISTENER__
#define __REC_UTIL_LISTENER_UNTYPEDADDRESSLISTENER__

#include "rec/util/listener/ProtoListener.h"
#include "rec/data/proto/Proto.h"

namespace rec {
namespace util {
namespace listener {

class ProtoAddressListener : public ProtoListener {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::UntypedData UntypedData;

  explicit ProtoAddressListener(const Address& a) : address_(a) {}

  virtual ~ProtoAddressListener() {}

  virtual void operator()(const Message& message) {
    set(proto::getValue(address_, message));
  }

  virtual const Address& address() const { return address_; }

 protected:
  // onChange is called when the local copy of the data is changed by the GUI,
  // to update the persistent data.
  virtual void updatePersistentData() {
    if (this->getData())
      this->getData()->set(address_, get());
  }

  // Gets the data from the "view".
  virtual const Value get() const = 0;

  // Set the "view" data.
  virtual void set(const Value&) = 0;

 private:
  const Address address_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(ProtoAddressListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_UNTYPEDADDRESSLISTENER__
