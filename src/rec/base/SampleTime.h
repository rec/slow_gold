#ifndef __REC_BASE_SAMPLETIME__
#define __REC_BASE_SAMPLETIME__

#include "rec/base/RealTime.h"

namespace rec {

struct SampleTime {
  SampleTime() {}

  // Conversion from integer types means "a sample count".
  SampleTime(int64 p) : position_(p) {}
  SampleTime(uint64 p) : position_(static_cast<int32>(p)) {}
  SampleTime(int p) : position_(p) {}
  SampleTime(short p) : position_(p) {}

  SampleTime& operator++() { ++position_; return *this; }
  SampleTime& operator--() { --position_; return *this; }

  SampleTime operator++(int) { return position_++; }
  SampleTime operator--(int) { return position_--; }

  SampleTime& operator-=(SampleTime p) { position_ -= p; return *this; }
  SampleTime& operator+=(SampleTime p) { position_ += p; return *this; }

  const SampleTime operator+(SampleTime p) { return position_ + p; }
  const SampleTime operator-(SampleTime p) { return position_ - p; }
  const SampleTime operator+(int p) { return position_ + p; }
  const SampleTime operator-(int p) { return position_ - p; }
  const SampleTime operator+(uint p) { return position_ + p; }
  const SampleTime operator-(uint p) { return position_ - p; }
  const SampleTime operator+(int64 p) { return position_ + p; }
  const SampleTime operator-(int64 p) { return position_ - p; }
  const SampleTime operator+(uint64 p) { return position_ + p; }
  const SampleTime operator-(uint64 p) { return position_ - p; }

  operator int64() const { return position_; }
  int64 get() { return position_; }

  RealTime toRealTime(int32 sampleRate) const {
    return static_cast<double>(position_) / static_cast<double>(sampleRate);
  }

  static SampleTime getSamplesPerSecond();
  static void setSamplesPerSecond(SampleTime);

  RealTime toRealTime() const {
    return static_cast<double>(position_) / getSamplesPerSecond();
  }

  SampleTime(RealTime time);

  // TODO: we shouldn't need this, but Juce sometimes wants ints.  Bug Jules!
  int toInt() const { return static_cast<int>(position_); }

 private:
  int64 position_;

 private:
  // Disallow these two constructors.
  SampleTime(float time);
  SampleTime(double time);

  JUCE_LEAK_DETECTOR(SampleTime);
};

}  // namespace rec

#endif  // __REC_BASE_SAMPLETIME__
