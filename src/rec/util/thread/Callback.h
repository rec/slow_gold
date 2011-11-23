#ifndef __REC_THREAD_CALLBACK__
#define __REC_THREAD_CALLBACK__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

// A generic callback.
class Callback {
 public:
  virtual bool operator()() = 0;
  virtual ~Callback() {}

 private:
  JUCE_LEAK_DETECTOR(Callback);
};

}  // namespace callback
}  // namespace thread

typedef thread::callback::Callback Callback;

}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_CALLBACK__
