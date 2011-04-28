#ifndef __REC_UTIL_THREAD_LOCKER__
#define __REC_UTIL_THREAD_LOCKER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace thread {

template <typename Data>
class Locker: public Listener<const Data&> {
 public:
  Locker(CriticalSection* l) : lock_(l), broadcaster_(NULL), changed_(false) {}

  virtual ~Locker() {}

  virtual void operator()(const Data& data) { set(data); }

  void listenTo(Broadcaster<const Data&>* b) {
    if (broadcaster_)
      broadcaster_->removeListener(this);

    broadcaster_ = b;

    if (broadcaster_)
      broadcaster_->addListener(this);
  }

  void broadcastIfChanged(Listener<const Data&>* listener) {
    Data data;
    {
      ScopedLock l(*lock_);
      if (!changed_)
        return;
      data = data_;
      changed_ = false;
    }
    (*listener)(data);
  }

  virtual void set(const Data& data) {
    ScopedLock l(*lock_);
    data_ = data;
    changed_ = true;
    onChange();
  }

 protected:
  virtual void onChange() {}

 private:
  CriticalSection* lock_;
  Broadcaster<const Data&>* broadcaster_;

  Data data_;
  bool changed_;
  DISALLOW_COPY_AND_ASSIGN(Locker);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOCKER__
