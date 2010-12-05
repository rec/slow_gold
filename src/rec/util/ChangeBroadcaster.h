#ifndef __REC_UTIL_CHANGEBROADCASTER__
#define __REC_UTIL_CHANGEBROADCASTER__

#include "rec/util/Broadcaster.h"

namespace rec {
namespace util {

template <typename Type>
class ChangeBroadcaster : public Broadcaster<Type> {
 public:
  virtual void operator()(Type x) {
    if (isChanged(x)) {
      data_ = x;
      broadcast(x);
    }
  }

  virtual bool isChanged(Type x) const { return data_ != x; }

 private:
  Type data_;
  DISALLOW_COPY_AND_ASSIGN(ChangeBroadcaster);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CHANGEBROADCASTER__
