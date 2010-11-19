#ifndef __REC_UTIL_LISTENER__
#define __REC_UTIL_LISTENER__

#include <glog/logging.h>
#include <set>

#include "rec/base/base.h"

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

    Listeners* listeners() { return &listeners_; }

    virtual void operator()(Type x) {
      for (iterator i = listeners_.begin(); i != listeners_.end(); ++i)
        (**i)(x);
    }

    virtual ~Set() {}

   private:
    Listeners listeners_;
  };
};




}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER__
