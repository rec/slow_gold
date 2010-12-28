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
  typedef std::set<Broadcaster<Type>*> Broadcasters;
  typedef typename Broadcasters::iterator iterator;

  Listener() {}
  virtual ~Listener();

  virtual void operator()(Type x) = 0;

 private:
  Broadcasters broadcasters_;

  friend class Broadcaster<Type>;
  DISALLOW_COPY_AND_ASSIGN(Listener);
};

// Broadcast updates of type Type to a set of Listener<Type>.
template <typename Type>
class Broadcaster : public Listener<Type> {
 public:
  typedef std::set<Listener<Type>*> Listeners;
  typedef typename Listeners::iterator iterator;

  Broadcaster() {}

  virtual ~Broadcaster();
  virtual void broadcast(Type x);
  virtual void operator()(Type t) { broadcast(t); }

  virtual void addListener(Listener<Type>* listener);
  virtual void removeListener(Listener<Type>* listener);

 protected:
  CriticalSection lock_;
  Listeners listeners_;

  DISALLOW_COPY_AND_ASSIGN(Broadcaster);
};

template <typename Type>
Listener<Type>::~Listener() {
  for (iterator i = broadcasters_.begin(); i != broadcasters_.end(); ++i)
    (*i)->removeListener(this);
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
void Broadcaster<Type>::addListener(Listener<Type>* listener) {
  DCHECK(listener != this);
  ScopedLock l(lock_);
  listeners_.insert(listener);
  listener->broadcasters_.insert(this);
}

template <typename Type>
void Broadcaster<Type>::removeListener(Listener<Type>* listener) {
  ScopedLock l(lock_);
  listeners_.erase(listener);
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
