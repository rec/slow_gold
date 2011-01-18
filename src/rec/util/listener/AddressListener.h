#ifndef __REC_UTIL_LISTENER_ADDRESSLISTENER__
#define __REC_UTIL_LISTENER_ADDRESSLISTENER__

#include "rec/util/listener/DataListener.h"

namespace rec {
namespace util {
namespace listener {

// AddressListener is a DataListener that's listening to a specific Address
// within that persistent data.
template <typename Proto>
class AddressListener : public DataListener<Proto> {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  explicit AddressListener(const Address& a) : address_(a) {}
  virtual ~AddressListener() {}

  virtual void operator()(const Proto& message) {
    setAndChange(proto::getValue(address_, message));
  }

  virtual const Address& address() const { return address_; }

 protected:
  void setAndChange(const Value& v) {
    set(v);
    onChange();
  }

  virtual void onChange() {
    if (this->getData())
      this->getData()->set(address_, get());
  }

  virtual const Value get() const = 0;
  virtual void set(const Value&) = 0;

 private:
  const Address address_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AddressListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_ADDRESSLISTENER__
