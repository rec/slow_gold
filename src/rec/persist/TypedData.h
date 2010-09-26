#ifndef __REC_PERSIST_TYPEDDATA__
#define __REC_PERSIST_TYPEDDATA__

#include <vector>

#include "rec/base/basictypes.h"
#include "rec/persist/Data.h"

namespace rec {
namespace persist {

class App;

template <typename Proto>
class TypedData : public Data {
 public:
  // Get a snapshot of the current data.
  Proto get() const;

  // Add a listener so you get notified every time the data changes.
  bool addListener(Listener* ls);
  bool removeListener(Listener* ls);

  // Request a change (same as on Data).
  virtual void change(Operation* op) { Data::change(op); }

  struct Listener {
    virtual void dataUpdate(const Proto& message) = 0;
    virtual ~Listener() {}
  };

  virtual ~TypedData() {}

 protected:
  virtual void changeCallback();

 private:
  friend class App;
  typedef std::set<Listener*> Listeners;

  TypedData(const File& file, App* app)
      : Data(file, &message_),
        app_(static_cast<App*>(app)) {
  }

  App* app_;
  Proto message_;
  Listeners listeners_
  CriticalSection listenerLock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TypedData);
};


// Implementation follows.

template <typename Proto>
Proto TypedData<Proto>::get() const {
  ScopedLock l(lock_);

  Proto p;
  p.CopyFrom(*message_);
  return p;
}

template <typename Proto>
bool TypedData<Proto>::addListener(Listener* ls) {
  ScopedLock l(listenerLock_);
  Listeners::iterator i = listeners_.find(ls);
  if (l != listeners_.end()) {
    LOG(ERROR) << "Tried to insert a listener twice.";
    return false;
  }
  listeners_.insert(ls);
  return true;
}

template <typename Proto>
bool TypedData<Proto>::removeListener(Listener* ls) {
  ScopedLock l(listenerLock_);
  Listeners::iterator i = listeners_.find(ls);
  if (l == listeners_.end()) {
    LOG(ERROR) << "Tried to remove a non-existent listener.";
    return false;
  }
  listeners_.erase(i);
  return true;
}

template <typename Proto>
void TypedData<Proto>::changeCallback() {
  Proto proto = get();
  ScopedLock l(listenerLock_);
  for (Listeners::iterator i = listeners_.begin(); i != listeners_.end(); ++i)
    i->dataUpdate(proto_);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_TYPEDDATA__
