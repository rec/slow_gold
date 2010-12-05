#ifndef __REC_UTIL_LISTENER_CHANGEBROADCASTER__
#define __REC_UTIL_LISTENER_CHANGEBROADCASTER__

#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace util {
namespace listener {

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

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_CHANGEBROADCASTER__
