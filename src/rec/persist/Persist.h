#ifndef __REC_PERSIST_PERSIST__
#define __REC_PERSIST_PERSIST__

#include "rec/base/base.h"
#include "rec/base/Cast.h"
#include "rec/persist/Copy.h"
#include "google/protobuf/message.h"

#include "juce_amalgamated.h"

namespace rec {
namespace persist {

inline File getAppDataFile(const String& name) {
  File app = File::getSpecialLocation(File::userApplicationDataDirectory);
  return app.getChildFile("recs/" + name + ".data");
}

template <typename Data, typename Parent>
class Persistent {
 public:
  Persistent(const File& file) : file_(file) {
    copy(file_, (Parent*) &data_);
  }

  const Data& operator*()  const { return data_; }
  const Data* operator->() const { return &data_; }

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
  void write() const { copy((const Parent&) data_, &file_); }

  File file_;
  Data data_;
  CriticalSection lock_;

//  DISALLOW_COPY_ASSIGN_AND_EMPTY(Persistent);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_PERSIST__
