#ifndef __REC_UTIL_THREAD_MULTILOCKER__
#define __REC_UTIL_THREAD_MULTILOCKER__

#include "rec/util/thread/Locker.h"
#include "rec/util/STL.h"

namespace rec {
namespace util {
namespace thread {

class MultiLocker {
 public:
  MultiLocker() {}
  ~MultiLocker() { stl::deleteMapPointers(&map_); }

  void broadcastIfSet() {
    ScopedLock l(lock_);
    for (LockerMap::iterator i = map_.begin(); i != map_.end(); ++i)
      i->second->broadcastIfSet();
  }

  template <typename Proto>
  void listenTo(Broadcaster<const Proto&>* b) {
    ScopedLock l(lock_);
    getLocker<Proto>()->listenTo(b);
  }

  template <typename Proto>
  void addListener(Listener<const Proto&>* listener) {
    ScopedLock l(lock_);
    getLocker<Proto>()->addListener(listener);
  }

  template <typename Proto>
  const Proto get() const {
    ScopedLock l(lock_);
    return getLocker<Proto>()->get();
  }

  template <typename Proto>
  persist::Data<Proto>* update(const VirtualFile& file) {
    persist::Data<Proto>* data = persist::setter<Proto>(file);
    Locker<Proto>* locker = getLocker<Proto>();
    locker->listenTo(data);
    (*locker)(data->get());

    return data;
  }

 protected:
  template <typename Proto>
  Locker<Proto>* getLocker() const {
    return stl::getOrCreate< Locker<Proto> >(&map_, Proto().GetTypeName());
  }

 private:
  typedef std::map<string, LockerBase*> LockerMap;
  mutable LockerMap map_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(MultiLocker);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_MULTILOCKER__
