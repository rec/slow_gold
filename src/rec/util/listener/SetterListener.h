#ifndef __REC_UTIL_LISTENER_SETTER__
#define __REC_UTIL_LISTENER_SETTER__

#include "rec/data/proto/Setter.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class SetterListener : public Listener<Proto> {
 public:
  typedef proto::arg::Setter Setter;
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;

  typedef Address A;
  typedef const A::Field& P;
  typedef const Message& M;

  SetterListener(Setter* s) : setter_(s) {}
  SetterListener(Setter* s, const Address& a) : address_(a), setter_(s) {}

  SetterListener(Setter* s, P a) : address_(a), setter_(s) {}
  SetterListener(Setter* s, P a, P b) : address_(a, b), setter_(s) {}
  SetterListener(Setter* s, P a, P b, P c) : address_(a, b, c), setter_(s) {}
  SetterListener(Setter* s, P a, P b, P c, P d) : address_(a, b, c, d), setter_(s) {}

  virtual void operator()(Proto v) {
    setter_->set(address_, Value(v));
  }

 private:
  const Address address_;
  Setter* setter_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_SETTER__
