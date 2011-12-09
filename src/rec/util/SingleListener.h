#ifndef __REC_UTIL_SINGLELISTENER__
#define __REC_UTIL_SINGLELISTENER__

#include "rec/util/Listener.h"

namespace rec {
namespace util {

template <typename Type, typename ListenTo = Broadcaster<Type> >
class SingleListener : public Listener<Type> {
 public:
  SingleListener() : listenTo_(NULL) {}

  void listenTo(ListenTo* b) {
    Lock l(listenerLock_);

    if (listenTo_)
      listenTo_->removeListener(this);
    listenTo_ = b;

    if (listenTo_)
      listenTo_->addListener(this);
  }

  ListenTo* getListenTo() const { return listenTo_; }

 private:
  ListenTo* listenTo_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SingleListener);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_SINGLELISTENER__
