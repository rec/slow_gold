#ifndef __REC_UTIL_THREAD_FACTORY__
#define __REC_UTIL_THREAD_FACTORY__

#include "rec/base/base.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {
namespace thread {

template <typename Product, typename Description>
class Factory : public listener::Broadcaster<Product>,
                public listener::Listener<Description> {
 public:
  Factory(Thread* thread = NULL) : thread_(thread) {}
  virtual Product makeProduct(Description) { return NULL; }

  virtual void operator()(Description desc) {
    ScopedLock l(this->lock_);
    typename listener::Broadcaster<Product>::iterator i = this->listeners_.begin();
    for (; i != this->listeners_.end() && !(thread_ && thread_->threadShouldExit()); ++i) {
      if (Product product = makeProduct(desc))
        (**i)(product);
    }
  }

 private:
  Thread* thread_;
  DISALLOW_COPY_AND_ASSIGN(Factory);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_FACTORY__
