#ifndef __REC_UTIL_BROADCASTER__
#define __REC_UTIL_BROADCASTER__

#include "rec/util/Listener.h"

namespace rec {
namespace util {

template <typename Type>
class Broadcaster : public Listener<Type> {
 public:
  typedef std::set<Listener*> Listeners;
  typedef typename Listeners::iterator iterator;

  void addListener(Listener* listener) {
    ScopedLock l(lock_);
    listeners_.insert(listener);
  }

  void removeListener(Listener* listener) {
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

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BROADCASTER__
