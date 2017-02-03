#pragma once

#include "rec/base/base.h"

namespace rec {
namespace audio {

// A class to represent 24-bit integers.
struct int24 {
  int value_;

  int24(int value) : value_(value) {}
  int24() {}

  operator int() const { return value_; }
  int24& operator=(int v) { value_ = v; return *this; }
  int24& operator=(int64 v) { value_ = static_cast<int>(v); return *this; }
};

template <typename From, typename To> void convertSample(From f, To* t);

}  // namespace audio
}  // namespace rec

