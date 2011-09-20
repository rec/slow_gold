#ifndef __REC_BASE_SAMPLEPOSITION__
#define __REC_BASE_SAMPLEPOSITION__

#include "rec/base/RealTime.h"

namespace rec {

struct SamplePosition {
  SamplePosition() : position_(0) {}
  SamplePosition(int64 p) : position_(p) {}
  SamplePosition(int p) : position_(p) {}
  SamplePosition(RealTime time) : position_(static_cast<int64>(44100 * time)) {}
  SamplePosition(float time) : position_(static_cast<int64>(44100 * time)) {}

  SamplePosition& operator++() { ++position_; return *this; }
  SamplePosition& operator--() { --position_; return *this; }

  SamplePosition operator++(int) { return position_++; }
  SamplePosition operator--(int) { return position_--; }

  SamplePosition& operator-=(SamplePosition p) { position_ -= p; return *this; }
  SamplePosition& operator+=(SamplePosition p) { position_ += p; return *this; }

  const SamplePosition operator+(SamplePosition p) { return position_ + p; }
  const SamplePosition operator-(SamplePosition p) { return position_ - p; }
  const SamplePosition operator+(int p) { return position_ + p; }
  const SamplePosition operator-(int p) { return position_ - p; }
  const SamplePosition operator+(int64 p) { return position_ + p; }
  const SamplePosition operator-(int64 p) { return position_ - p; }

  int64 position_;
  operator int64() const { return position_; }
};

}  // namespace rec

#endif  // __REC_BASE_SAMPLEPOSITION__
