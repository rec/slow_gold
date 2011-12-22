#ifndef __REC_UTIL_LISTENER_LISTENER__
#define __REC_UTIL_LISTENER_LISTENER__

#include <map>
#include <set>

#include "rec/base/base.h"

namespace rec {
namespace util {

inline bool *listenersEnabled() {
  static bool enabled = true;
  return &enabled;
}

template <typename Type> class Broadcaster;

template <typename Type>
class Listener {
 public:
  typedef std::set<Broadcaster<Type>*> BroadcasterSet;
  typedef typename BroadcasterSet::iterator iterator;

  Listener() {}
  virtual ~Listener();

  virtual void operator()(Type x) = 0;

  const CriticalSection& lock() const { return listenerLock_; }
  int broadcasterSize() const { return broadcasters_.size(); }

 protected:
  CriticalSection listenerLock_;

 private:
  virtual void wasRemovedFrom(Broadcaster<Type>*);
  void wasAddedTo(Broadcaster<Type>*);

  BroadcasterSet broadcasters_;

  DISALLOW_COPY_AND_ASSIGN(Listener);
  JUCE_LEAK_DETECTOR(Listener<Type>);

  friend class Broadcaster<Type>;
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

  virtual void addListener(Listener<Type>* listener);
  virtual void removeListener(Listener<Type>* listener);

  int listenerSize() const { return listeners_.size(); }

 protected:
  CriticalSection broadcasterLock_;
  ListenerSet listeners_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Broadcaster);
  JUCE_LEAK_DETECTOR(Broadcaster<Type>);
};

template <typename Type>
Listener<Type>::~Listener() {
  DLOG(INFO) << "~Listener " << this;
  BroadcasterSet toDelete;
  {
    Lock l(listenerLock_);
    if (broadcasters_.empty())
      return;

    broadcasters_.swap(toDelete);
  }

  for (iterator i = toDelete.begin(); i != toDelete.end(); ++i) {
    DLOG(INFO) << "removing listener from " << *i;
    (*i)->removeListener(this);
  }
  DLOG(INFO) << "~Listener DONE";
}

template <typename Type>
void Listener<Type>::wasRemovedFrom(Broadcaster<Type>* broadcaster) {
  Lock l(listenerLock_);
  broadcasters_.erase(broadcaster);
}

template <typename Type>
void Listener<Type>::wasAddedTo(Broadcaster<Type>* broadcaster) {
  Lock l(listenerLock_);
  broadcasters_.insert(broadcaster);
}

template <typename Type>
void Broadcaster<Type>::broadcast(Type x) {
  Lock l(broadcasterLock_);
  for (iterator i = listeners_.begin(); i != listeners_.end(); ++i) {
    Listener<Type>* listener = *i;
    Lock m(listener->listenerLock_);
    (*listener)(x);
  }
}

template <typename Type>
Broadcaster<Type>::~Broadcaster() {
  DLOG(INFO) << "~Broadcaster " << this;
  Lock l(broadcasterLock_);
  for (iterator i = listeners_.begin(); i != listeners_.end(); ++i) {
    DLOG(INFO) << "removing broadcaster from " << *i;
    (*i)->wasRemovedFrom(this);
  }
  DLOG(INFO) << "~Broadcaster DONE";
}

template <typename Type>
void Broadcaster<Type>::addListener(Listener<Type>* listener) {
  DCHECK(*listenersEnabled());
  DLOG(INFO) << "addListener " << this << ", " << listener;
  {
    Lock l(broadcasterLock_);
    listeners_.insert(listener);
  }

  listener->wasAddedTo(this);
  DLOG(INFO) << "addListener DONE";
}

template <typename Type>
void Broadcaster<Type>::removeListener(Listener<Type>* listener) {
  DLOG(INFO) << "removeListener " << this << ", " << listener;
  {
    Lock l(broadcasterLock_);
    listeners_.erase(listener);
  }

  listener->wasRemovedFrom(this);
  DLOG(INFO) << "removeListener DONE";
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_LISTENER__
