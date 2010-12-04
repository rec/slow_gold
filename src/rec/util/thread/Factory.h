#ifndef __REC_UTIL_THREAD_FACTORY__
#define __REC_UTIL_THREAD_FACTORY__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

template <typename Product, typename Description>
class Factory : public Listener::Set<Product*>,
                public ChangeLocker<Description> {
 public:
  Factory() {}

  virtual void operator()(Description desc) {
    ScopedLock l(lock_);
    Listeners::iterator i = listeners_.begin();
    for (; i != listeners_.end() && !threadShouldExit(); ++i)
      (*i)(new Product(desc));
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Factory);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_FACTORY__
