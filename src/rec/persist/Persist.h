#ifndef __REC_PERSIST_PERSIST__
#define __REC_PERSIST_PERSIST__

#include "rec/base/base.h"
#include "rec/persist/Copy.h"

#include "juce_amalgamated.h"

namespace rec {
namespace persist {

template <typename Data, typename Storage>
class Persistent {
 public:
  Persistent(Storage storage) : storage_(storage) {
    read();
  }

  friend class Accessor;

  class Accessor : public ScopedLock {
   public:
    Accessor(Persistent* p) : ScopedLock(p->lock_), persistent_(p) {}
    ~Accessor() {
      persistent_->write();
    }

    Data& operator*()  const { return persistent_->data_; }
    Data* operator->() const { return &persistent_->data_; }

   private:
    Persistent* persistent_;
    DISALLOW_COPY_ASSIGN_AND_EMPTY(Accessor);
  };

 private:
  void read()        { copy(*storage_, &data_); }
  void write() const { copy(data_, storage_); }

  Storage storage_;
  Data data_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Persistent);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_PERSIST__
