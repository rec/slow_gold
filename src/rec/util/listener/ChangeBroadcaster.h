#ifndef __REC_UTIL_LISTENER_CHANGEBROADCASTER__
#define __REC_UTIL_LISTENER_CHANGEBROADCASTER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace listener {

template <typename Type>
class ChangeBroadcaster : public Broadcaster<const Type&> {
 public:
  ChangeBroadcaster() {}
  virtual void operator()(const Type& x) {
    if (isChanged(x, data_)) {
      data_ = x;
      broadcast(x);
    }
  }

  virtual bool isChanged(const Type& x, const Type& y) const = 0;

 private:
  Type data_;
  DISALLOW_COPY_AND_ASSIGN(ChangeBroadcaster);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_CHANGEBROADCASTER__
