#ifndef __REC_AUDIO_SOURCE_DOUBLE__
#define __REC_AUDIO_SOURCE_DOUBLE__

#include "rec/base/base.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/util/ChangeLocker.h"

namespace rec {
namespace audio {
namespace source {

typedef util::ChangeLocker<StretchyDesc> ChangeLocker;

template <typename Description, typename Result>
class Double : public ChangeLocker<Description>,
               public Broadcaster<Result*> {
 public:
  Double(const Data& data, int wait) : ChangeLocker<Data>(data, wait) {}
  virtual void operator()(Data data) {
    broadcast(new Result(data));
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Double);
};

template <typename Data>
class Locker {
 public:
  Locker(const Data& desc) : desc_(desc), changed_(false) {}

  void setDesc(const Data& desc) {
    ScopedLock l(lock_);
    desc_ = desc;
    changed_ = true;
  }

  const Data getDesc() const {
    ScopedLock l(lock_);
    return desc_;
  }

  bool changed() const {
    ScopedLock l(lock_);
    return changed_;
  }

 private:
  CriticalSection lock_;
  Data desc_;
  bool changed_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Locker);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLE__
