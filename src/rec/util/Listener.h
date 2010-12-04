#ifndef __REC_UTIL_LISTENER__
#define __REC_UTIL_LISTENER__

#include <glog/logging.h>
#include <set>

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace util {

template <typename Type>
class Listener {
 public:
  virtual void operator()(Type x) = 0;
  virtual ~Listener() {}

  class Set : public Listener<Type> {
   public:
    typedef std::set<Listener*> Listeners;
    typedef typename Listeners::iterator iterator;

    Set() {}
    virtual ~Set() {}

    void addListener(Listener* listener) {
      ScopedLock l(lock_);
      listeners_.insert(listener);
    }

    void removeListener(Listener* listener) {
      ScopedLock l(lock_);
      listeners_.remove(listener);
    }

    void tellListeners(Type x) {
      ScopedLock l(lock_);
      for (iterator i = listeners_.begin(); i != listeners_.end(); ++i)
        (**i)(x);
    }

    virtual void operator()(Type x) {
      tellListeners(x);
    }

   protected:
    CriticalSection lock_;
    Listeners listeners_;
    DISALLOW_COPY_AND_ASSIGN(Set);
  };
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER__
