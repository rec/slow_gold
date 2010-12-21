#ifndef __REC_UTIL_LISTENER_BROADCASTER__
#define __REC_UTIL_LISTENER_BROADCASTER__

#include <set>

#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace listener {

// Broadcast updates of type Type to a set of Listener<Type>.
template <typename Type>
class Broadcaster : public Listener<Type> {
 public:
  typedef std::set<Listener<Type>*> Listeners;
  typedef typename Listeners::iterator iterator;

  Broadcaster() {}
  virtual ~Broadcaster() {}

  virtual void addListener(Listener<Type>* listener) {
    ScopedLock l(lock_);
    listeners_.insert(listener);
  }

  virtual void removeListener(Listener<Type>* listener) {
    ScopedLock l(lock_);
    listeners_.erase(listener);
  }

  virtual void broadcast(Type x) {
    ScopedLock l(lock_);
    for (iterator i = listeners_.begin(); i != listeners_.end(); ++i)
      (**i)(x);
  }

  virtual void operator()(Type t) { broadcast(t); }

 protected:
  CriticalSection lock_;
  Listeners listeners_;
  DISALLOW_COPY_AND_ASSIGN(Broadcaster);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_BROADCASTER__
