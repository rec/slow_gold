#ifndef __REC_UTIL_THREAD_TIMESLICECLIENT__
#define __REC_UTIL_THREAD_TIMESLICECLIENT__

#include "rec/util/thread/Callback.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

class TimeSliceClient : public juce::TimeSliceClient,
                        public OwnedPointer<Callback> {
 public:
  TimeSliceClient(Callback* r = NULL) : OwnedPointer<Callback>(r) {}
  virtual bool useTimeSlice() { return (*this)(); }
};

}  // namespace client
}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_TIMESLICECLIENT__
