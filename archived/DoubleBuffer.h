#ifndef __REC_DOUBLE_BUFFER
#define __REC_DOUBLE_BUFFER

#include "rec/base/scoped_ptr.h"
#include "rec/util/locker.h"
#include "rec/util/CircularEnum.h"

namespace rec {
namespace buffer {

template <typename Buffer, int SIZE, typename Notifier>
class MultiBuffer {
 public:
  enum State { EMPTY, FULL, BEING_EMPTIED };

  MultiBuffer(LockInterface* lock, Notifier notifier)
      : lock_(lock), notifier_(notifier), end_(buffers_ + SIZE) {
  }

  FillableBuffer* getEmpty() {
    Locker l(lock_.get());

    for (Fillable i = buffers_; i != end && i->state != EMPTY; ++i);
    return (empty == end_) ? NULL : empty;
  }

  FillableBuffer* getFull() {
    Locker l(lock_.get());

    for (Fillable *i = end_; buffers_ != i--;) {
      if (i->state == FULL) {
        i->state = BEING_EMPTIED;
        notifier_();
        return i;
      }
    }
    return NULL;
  }

  void setState(FillableBuffer* buffer, State) {
    Locker l(lock_.get());
    buffer->state = state;
  }

 private:
  struct FillableBuffer {
    FillableBuffer() : state(EMPTY) {}
    State state;
    Buffer buffer;
  };

  scoped_ptr<LockInterface> lock_;
  Notifier notifier_;

  FillableBuffer buffers_[SIZE];
  FillableBuffer* end_;

  DISALLOW_COPY_AND_ASSIGN(MultiBuffer);
};

}  // namespace buffer
}  // namespace rec


#endif  // __REC_DOUBLE_BUFFER
