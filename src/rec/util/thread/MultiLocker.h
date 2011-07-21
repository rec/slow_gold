#ifndef __REC_UTIL_THREAD_MULTILOCKER__
#define __REC_UTIL_THREAD_MULTILOCKER__

#include "rec/util/thread/Locker.h"
#include "rec/util/STL.h"

namespace rec {
namespace util {
namespace thread {

class LockerBase {
 public:
  LockerBase() : changed_(false) {}
  virtual ~LockerBase() {}

  void broadcastIfChanged() {
    if (changed_)
      broadcastData();
    changed_ = false;
  }

  virtual void broadcastData() = 0;
  virtual void update(const VirtualFile&) = 0;

 protected:
  bool changed_;
};

template <typename Proto>
class ProtoLocker: public LockerBase,
                   public Listener<const Proto&>,
                   public Broadcaster<const Proto&> {
 public:
  ProtoLocker() : data_(NULL) {}
  virtual ~ProtoLocker() {}

  virtual void operator()(const Proto& proto) { set(proto); }
  virtual void broadcastData() { broadcast(proto_); }

  void set(const Proto& d) { proto_ = proto; changed_ = true; }
  const Proto get() { return proto_; }

  virtual void update(const VirtualFile& file) {
    if (data_)
      data_->removeListener(this);

    data_ = persist::setter<Proto>(file);

    if (data_)
      data_->addListener(this);
  }

 private:
  Proto proto_;
  persist::Data<Proto>* data_;

  DISALLOW_COPY_AND_ASSIGN(ProtoLocker);
};

void ProtoLocker<VirtualFile>::update(const VirtualFile&) {}  // Do nothing.

class MultiLocker {
 public:
  MultiLocker() {}
  ~MultiLocker() { stl::deleteMapPointers(&map_); }

  void broadcastIfChanged() {
    ScopedLock l(lock_);
    for (LockerMap::iterator i = map_.begin(); i != map_.end(); ++i)
      i->second->broadcastIfChanged();
  }

  void update(const VirtualFile& file) {
    ScopedLock l(lock_);
    file_ = file;
    for (LockerMap::iterator i = map_.begin(); i != map_.end(); ++i)
      i->second->update(file);
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
  void set(const Proto& proto) const {
    ScopedLock l(lock_);
    getLocker<Proto>()->set(proto);
  }

 protected:
  template <typename Proto>
  ProtoLocker<Proto>* getLocker() const {
    typedef ProtoLocker<Proto> Locker;
    const string& protoName = Proto().GetTypeName();

    ScopedLock l(lock_);
    LockerMap::iterator i = map_.find(protoName);
    if (i == map_.end())
      return dynamic_cast<Locker>(i->second);

    Locker* locker = new Locker();
    locker->update(file);
    map_[protoName] = locker;

    return locker;
  }

 private:
  typedef std::map<string, LockerBase*> LockerMap;

  CriticalSection lock_;
  VirtualFile file_;
  mutable LockerMap map_;

  DISALLOW_COPY_AND_ASSIGN(MultiLocker);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_MULTILOCKER__
