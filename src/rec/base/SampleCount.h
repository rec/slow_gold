#ifndef __REC_BASE_SAMPLECOUNT__
#define __REC_BASE_SAMPLECOUNT__

#include "rec/base/RealTime.h"

namespace rec {

template <int SAMPLES_PER_SEC>
struct SampleCount {
  template <typename Type>
  int64 cast(Type t) const { return static_cast<int64>(SAMPLES_PER_SEC * t); }

  SampleCount() : position_(0) {}
  SampleCount(int64 p) : position_(p) {}
  SampleCount(int p) : position_(p) {}
  SampleCount(short p) : position_(p) {}

  SampleCount(RealTime time) : position_(cast(time)) {}
  SampleCount(float time) : position_(cast(time)) {}
  SampleCount(double time) : position_(cast(time)) {}

  SampleCount& operator++() { ++position_; return *this; }
  SampleCount& operator--() { --position_; return *this; }

  SampleCount operator++(int) { return position_++; }
  SampleCount operator--(int) { return position_--; }

  SampleCount& operator-=(SampleCount p) { position_ -= p; return *this; }
  SampleCount& operator+=(SampleCount p) { position_ += p; return *this; }

  const SampleCount operator+(SampleCount p) { return position_ + p; }
  const SampleCount operator-(SampleCount p) { return position_ - p; }
  const SampleCount operator+(int p) { return position_ + p; }
  const SampleCount operator-(int p) { return position_ - p; }
  const SampleCount operator+(int64 p) { return position_ + p; }
  const SampleCount operator-(int64 p) { return position_ - p; }

  operator int64() const { return position_; }

  // TODO: we shouldn't need this, but Juce sometimes wants ints.  Bug Jules!
  int toInt() const { return static_cast<int>(position_); }

 private:
  int64 position_;
};

typedef SampleCount<44100> SamplePosition;

}  // namespace rec

#endif  // __REC_BASE_SAMPLECOUNT__
