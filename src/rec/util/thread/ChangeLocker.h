#ifndef __REC_UTIL_CHANGELOCKER__
#define __REC_UTIL_CHANGELOCKER__

#include "rec/base/base.h"
#include "rec/util/Broadcaster.h"

namespace rec {
namespace util {
namespace thread {

template <typename Data>
class ChangeLocker : public Thread, public Broadcaster<Data> {
 public:
  ChangeLocker(int wait) : wait_(wait) {}

  void set(const Data& data) {
    dataLocker_.set(data);
    notify();
  }

  virtual void run() {
    Data data;
    while (!threadShouldExit()) {
      if (dataLocker_.getDataIfChanged(&data) && !threadShouldExit())
        (*this)(data);

      if (!threadShouldExit())
        wait(wait_);
    }
  }

 private:
  Locker<Data> dataLocker_;
  const int wait_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(ChangeLocker);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CHANGELOCKER__
