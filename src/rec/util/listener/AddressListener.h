#ifndef __REC_UTIL_LISTENER_ADDRESSLISTENER__
#define __REC_UTIL_LISTENER_ADDRESSLISTENER__

#include "rec/util/listener/DataListener.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class AddressListener : public DataListener<Proto> {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  explicit AddressListener(const Address& a) : address_(a) {}

  virtual ~AddressListener() {}

  virtual void operator()(const Proto& message) {
    set(proto::getValue(address_, message));
  }

  virtual const Address& address() const { return address_; }

 protected:
  // onChange is called when the local copy of the data is changed by the GUI,
  // to update the persistent data.
  virtual void onChange() {
    if (this->getData())
      this->getData()->set(address_, get());
  }

  // Gets the data from the "view".
  virtual const Value get() const = 0;

  // Set the "view" data.
  virtual void set(const Value&) = 0;

 private:
  const Address address_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AddressListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_ADDRESSLISTENER__
