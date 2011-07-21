#ifndef __REC_AUDIO_UTIL_CONVERTSAMPLE__
#define __REC_AUDIO_UTIL_CONVERTSAMPLE__

#include "rec/base/base.h"

namespace rec {
namespace audio {

// A class to represent 24-bit integers.
typedef struct int24 {
  int value_;

  int24(int value) : value_(value) {}
  int24() {}

  operator int() const { return value_; }
  int24& operator=(int value) { value_ = value; return *this; }
};

template <typename From, typename To> void convertSample(From f, To* t);

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_CONVERTSAMPLE__
