#ifndef __REC_UTIL_LISTENER_SETTER__
#define __REC_UTIL_LISTENER_SETTER__

#include "rec/data/Data.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class SetterListener : public Listener<Proto> {
 public:
  typedef const data::Address::Part& P;

  SetterListener(Data* s) : setter_(s) {}
  SetterListener(Data* s, const data::Address& a) : address_(a), setter_(s) {}

  SetterListener(Data* s, P a) : address_(a), setter_(s) {}
  SetterListener(Data* s, P a, P b) : address_(a, b), setter_(s) {}
  SetterListener(Data* s, P a, P b, P c) : address_(a, b, c), setter_(s) {}
  SetterListener(Data* s, P a, P b, P c, P d) : address_(a, b, c, d), setter_(s) {}

  virtual void operator()(Proto v) {
    setter_->set(address_, Value(v));
  }

 private:
  const data::Address address_;
  data::Editable* setter_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterListener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_SETTER__
