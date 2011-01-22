#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/util/Reference.h"
#include "rec/data/persist/Data.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/persist/App.h"

namespace rec {
namespace util {
namespace listener {

// DataListener listens to changes in peristent data and contains a
// a reference to the data it's listening to.

template <typename Proto>
class DataListener : public Reference<persist::Data<Proto> >,
                     public Listener<const Proto&> {
 public:
  typedef persist::Data<Proto> Data;

  DataListener() {}
  virtual ~DataListener() {}
  virtual void operator()(const Proto&) = 0;

  virtual void setData(Data* d) {
    if (this->getData())
      this->getData()->removeListener(this);

    Reference<Data>::setData(d);

    if (this->getData())
      this->getData()->addListener(this);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(DataListener);
};

#if 0
class SetterListener : public Reference<Setter>, public Listener<const Message&> {
 public:
  SetterListener() {}
  virtual ~SetterListener() {}
  virtual void operator()(const Message&) = 0;

  virtual void setData(Setter* s) {
    if (this->getData())
      this->getData()->removeListener(this);

    Super::setData(d);

    if (this->getData())
      this->getData()->addListener(this);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(SetterListener);
};
#endif

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
