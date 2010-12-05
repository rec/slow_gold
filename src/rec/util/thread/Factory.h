#ifndef __REC_UTIL_THREAD_FACTORY__
#define __REC_UTIL_THREAD_FACTORY__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

template <typename Product, typename Description>
class Factory : public Broadcaster<Product*>, public Listener<Description> {
 public:
  Factory() {}

  virtual Product* makeProduct(Description) { return NULL; }

  virtual void operator()(Description desc) {
    ScopedLock l(lock_);
    Listeners::iterator i = listeners_.begin();
    for (; i != listeners_.end() && !threadShouldExit(); ++i) {
      if (Product* product = makeProduct(desc))
        (*i)(product);
    }
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Factory);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_FACTORY__
