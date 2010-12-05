#ifndef __REC_UTIL_LISTENER_BROADCASTER__
#define __REC_UTIL_LISTENER_BROADCASTER__

#include <set>

#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace listener {

template <typename Type>
class Broadcaster : public Listener<Type> {
 public:
  Broadcaster() {}
  typedef std::set<Listener<Type>*> Listeners;
  typedef typename Listeners::iterator iterator;

  void addListener(Listener<Type>* listener) {
    ScopedLock l(lock_);
    listeners_.insert(listener);
  }

  void removeListener(Listener<Type>* listener) {
    ScopedLock l(lock_);
    listeners_.remove(listener);
  }

  void broadcast(Type x) {
    ScopedLock l(lock_);
    for (iterator i = listeners_.begin(); i != listeners_.end(); ++i)
      (**i)(x);
  }

  virtual void operator()(Type x) {
    broadcast(x);
  }

 protected:
  CriticalSection lock_;
  Listeners listeners_;
  DISALLOW_COPY_AND_ASSIGN(Broadcaster);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_BROADCASTER__
