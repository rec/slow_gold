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

  Listener() : state_(LISTENING) {}
  virtual ~Listener();

  virtual void operator()(Type x) = 0;

  const CriticalSection& lock() const { return listenerLock_; }
  virtual void wasRemovedFrom(Broadcaster<Type>*);

 protected:
  CriticalSection listenerLock_;

 private:
  enum ListenerState { LISTENING, UPDATING, DELETING };
  CriticalSection stateLock_;

  bool setState(ListenerState);

  ListenerState state_;

  BroadcasterSet broadcasters_;

  DISALLOW_COPY_AND_ASSIGN(Listener);
  JUCE_LEAK_DETECTOR(Listener<Type>);

  friend class Broadcaster<Type>;
};

template <typename Type, typename ListenTo>
void listenTo(Listener<Type>* listener, ListenTo* newValue, ListenTo** target) {
  Lock l(listener->lock());
  if (*target)
    (*target)->removeListener(listener);

  *target = newValue;

  if (*target)
    (*target)->addListener(listener);
}

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
  setState(DELETING);

  BroadcasterSet toDelete;
  {
    Lock l(listenerLock_);
    if (broadcasters_.empty())
      return;

    broadcasters_.swap(toDelete);
  }

  for (iterator i = toDelete.begin(); i != toDelete.end(); ++i)
    (*i)->removeListener(this);
}

template <typename Type>
void Listener<Type>::wasRemovedFrom(Broadcaster<Type>* broadcaster) {
  Lock l(listenerLock_);
  broadcasters_.erase(broadcaster);
}


template <typename Type>
bool Listener<Type>::setState(ListenerState state) {
  while (true) {
    Lock l(stateLock_);
    if (state_ == DELETING) {
      return false;
    } else if (state == LISTENING) {
      state_ = state;
      return true;
    } else if (state_ == LISTENING) {
      state_ = state;
      return true;
    }
    Thread::sleep(1);
  }
};

template <typename Type>
void Broadcaster<Type>::broadcast(Type x) {
  Lock l(broadcasterLock_);
  for (iterator i = listeners_.begin(); i != listeners_.end(); ++i) {
    Listener<Type>* listener = *i;
    if (listener->setState(Listener<Type>::UPDATING)) {
      (*listener)(x);
      listener->setState(Listener<Type>::LISTENING);
    }
  }
}

template <typename Type>
Broadcaster<Type>::~Broadcaster() {
  for (iterator i = listeners_.begin(); i != listeners_.end(); ++i)
    (*i)->broadcasters_.erase(this);
}

template <typename Type>
void Broadcaster<Type>::addListener(Listener<Type>* listener) {
  {
    Lock l(broadcasterLock_);
    listeners_.insert(listener);
  }

  {
    Lock l(listener->listenerLock_);
    listener->broadcasters_.insert(this);
  }
}

template <typename Type>
void Broadcaster<Type>::removeListener(Listener<Type>* listener) {
  {
    Lock l(broadcasterLock_);
    listeners_.erase(listener);
  }

  listener->wasRemovedFrom(this);
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
