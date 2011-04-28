#ifndef __REC_UTIL_LISTENER_LISTENER__
#define __REC_UTIL_LISTENER_LISTENER__

#include <set>

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace listener {

template <typename Type> class Broadcaster;

template <typename Type>
class Listener {
 public:
  typedef std::set<Broadcaster<Type>*> BroadcasterSet;
  typedef typename BroadcasterSet::iterator iterator;

  Listener() {}
  virtual ~Listener();

  virtual void operator()(Type x) = 0;

 private:
  CriticalSection listenerLock_;
  BroadcasterSet broadcasters_;

  friend class Broadcaster<Type>;
  DISALLOW_COPY_AND_ASSIGN(Listener);
};

//
// Broadcast updates of type Type to a set of Listener<Type>.
//
template <typename Type>
class Broadcaster {
 public:
  typedef std::set<Listener<Type>*> ListenerSet;
  typedef typename ListenerSet::iterator iterator;

  Broadcaster() {}
  virtual ~Broadcaster();

  virtual void broadcast(Type x);
  virtual void broadcast() { broadcast(broadcastValue()); }

  virtual void addListener(Listener<Type>* listener, bool update = false);
  virtual void removeListener(Listener<Type>* listener);
  virtual const Type broadcastValue() const { return Type(); }

 protected:
  CriticalSection lock_;
  ListenerSet listeners_;

  DISALLOW_COPY_AND_ASSIGN(Broadcaster);
};

template <typename Type>
Listener<Type>::~Listener() {
  for (bool finished = false; !finished; ) {
    BroadcasterSet toDelete;
    {
      ScopedLock l(listenerLock_);
      if (broadcasters_.empty()) {
        finished = true;
        continue;
      }

      broadcasters_.swap(toDelete);
    }

    for (iterator i = toDelete.begin(); i != toDelete.end(); ++i)
      (*i)->removeListener(this);
  }
}

template <typename Type>
void Broadcaster<Type>::broadcast(Type x) {
  ScopedLock l(lock_);
  for (iterator i = listeners_.begin(); i != listeners_.end(); ++i)
    (**i)(x);
}

template <typename Type>
Broadcaster<Type>::~Broadcaster() {
  for (iterator i = listeners_.begin(); i != listeners_.end(); ++i)
    (*i)->broadcasters_.erase(this);
}

template <typename Type>
void Broadcaster<Type>::addListener(Listener<Type>* listener, bool update) {
  ScopedLock l(lock_);
  listeners_.insert(listener);

  {
    ScopedUnlock u(lock_);
    ScopedLock l(listener->listenerLock_);
    listener->broadcasters_.insert(this);
  }

  if (update)
    (*listener)(broadcastValue());
}

template <typename Type>
void Broadcaster<Type>::removeListener(Listener<Type>* listener) {
  {
    ScopedLock l(lock_);
    listeners_.erase(listener);
  }

  ScopedLock l(listener->listenerLock_);
  listener->broadcasters_.erase(this);
}

template <typename Type>
void add(Broadcaster<Type>* broadcaster, Listener<Type>* listener) {
  broadcaster->addListener(listener);
}

template <typename Type>
void remove(Broadcaster<Type>* broadcaster, Listener<Type>* listener) {
  broadcaster->removeListener(listener);
}

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_LISTENER__
