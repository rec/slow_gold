#ifndef __REC_BASE_REALTIME__
#define __REC_BASE_REALTIME__

#include "rec/util/Range.h"

namespace rec {

struct SamplePosition;

struct RealTime {
  RealTime() : time_(0) {}
  RealTime(double p) : time_(p) {}
  RealTime(float p) : time_(p) {}
  RealTime(int64 time) : time_(time / 44100.0) {}
  RealTime(int time) : time_(time / 44100.0) {}
  RealTime(const SamplePosition& pos);

  const RealTime operator+(RealTime p) { return time_ + p; }
  const RealTime operator-(RealTime p) { return time_ - p; }
  const RealTime operator+(double p) { return time_ + p; }
  const RealTime operator-(double p) { return time_ - p; }
  const RealTime operator+(float p) { return time_ + p; }
  const RealTime operator-(float p) { return time_ - p; }

  RealTime& operator-=(RealTime t) { time_ -= t; return *this; }
  RealTime& operator+=(RealTime t) { time_ += t; return *this; }
  RealTime& operator/=(RealTime t) { time_ /= t; return *this; }
  RealTime& operator*=(RealTime t) { time_ *= t; return *this; }

  double time_;
  operator double() const { return time_; }
};

}  // namespace rec

#endif  // __REC_BASE_REALTIME__
