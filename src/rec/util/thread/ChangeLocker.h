#ifndef __REC_UTIL_CHANGELOCKER__
#define __REC_UTIL_CHANGELOCKER__

#include "rec/base/base.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/Locker.h"

namespace rec {
namespace util {
namespace thread {

template <typename Data>
class ChangeLocker : public Thread,
                     public listener::Broadcaster<const Data&>,
                     public listener::Listener<Data>,
                     public Locker<Data> {
 public:
  ChangeLocker(int wait) : Thread("ChangeLocker"), wait_(wait) {}

  virtual void run() {
    Data data;
    while (!threadShouldExit()) {
      if (getDataIfChanged(&data) && !threadShouldExit())
        broadcast(data);

      if (!threadShouldExit())
        wait(wait_);
    }
  }

  virtual void operator()(const Data& data) { set(data); }
  virtual void operator()(Data data) { set(data); }

 protected:
  virtual void onChange() { notify(); }

 private:
  const int wait_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(ChangeLocker);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CHANGELOCKER__
