#ifndef __REC_UTIL_LISTENER_REBROADCASTER__
#define __REC_UTIL_LISTENER_REBROADCASTER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace listener {

template <typename Type>
class Rebroadcaster : public Listener<Type>, public Broadcaster<Type> {
 public:
  Rebroadcaster() {}
  virtual void operator()(Type x) { this->broadcast(x); }


 private:
  DISALLOW_COPY_AND_ASSIGN(Rebroadcaster);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_REBROADCASTER__
