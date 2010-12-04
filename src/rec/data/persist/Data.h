#ifndef __REC_PERSIST_DATA__
#define __REC_PERSIST_DATA__

#include <set>
#include <glog/logging.h>

#include "rec/base/base.h"
#include "rec/data/persist/UntypedData.h"

namespace rec {
namespace persist {

class App;

template <typename Proto>
class Data : public UntypedData {
 public:
  // Get a snapshot of the current data.
  Proto get() const;

  typedef util::Listener<const Proto&> Listener;

  // Add a listener so you get notified every time the data changes.
  bool addListener(Listener* ls);
  bool removeListener(Listener* ls);
  virtual void operator()(proto::Operation* op) { UntypedData::operator()(op); }

  virtual ~Data() {}

 protected:
  virtual void changeCallback();

 private:
  friend class App;
  typedef std::set<Listener*> Listeners;

  Data(const File& file, App* app) : UntypedData(file, &proto_, app) {}

  Proto proto_;
  Listeners listeners_;
  CriticalSection listenerLock_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Data);
};


// Implementation follows.

template <typename Proto>
Proto Data<Proto>::get() const {
  ScopedLock l(*lock_);

  Proto p;
  readFromFile();
  p.CopyFrom(proto_);
  return p;
}

template <typename Proto>
bool Data<Proto>::addListener(Listener* ls) {
  ScopedLock l(listenerLock_);
  typename Listeners::iterator i = listeners_.find(ls);
  if (l != listeners_.end()) {
    LOG(ERROR) << "Tried to insert a listener twice.";
    return false;
  }
  listeners_.insert(ls);
  return true;
}

template <typename Proto>
bool Data<Proto>::removeListener(Listener* ls) {
  ScopedLock l(listenerLock_);
  typename Listeners::iterator i = listeners_.find(ls);
  if (l == listeners_.end()) {
    LOG(ERROR) << "Tried to remove a non-existent listener.";
    return false;
  }
  listeners_.erase(i);
  return true;
}

template <typename Proto>
void Data<Proto>::changeCallback() {
  Proto proto = get();

  ScopedLock l(listenerLock_);
  typename Listeners::iterator i;
  for (i = listeners_.begin(); i != listeners_.end(); ++i)
    (**i)(proto);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATA__
