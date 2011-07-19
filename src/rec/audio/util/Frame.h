#if 0

#ifndef __REC_AUDIO_UTIL_FRAME__
#define __REC_AUDIO_UTIL_FRAME__

#include "rec/base/SamplePosition.h"

namespace rec {

template <typename Sample, int CHANNELS> 
struct OneFrame {
 Sample sample_[CHANNELS];
};

namespace persist {


template <typename S, typename T, int CHANNELS>
bool copy(const OneFrame<S, CHANNELS>& from, const OneFrame<T, CHANNELS>* to) {
  for (int i = 0; i < CHANNELS; ++i) {
    if (!copy(from.sample_[i], to + i))
      return false;
  }
  return true;
}

// A class to represent 24-bit integers.
typedef struct int24 {
  int value_;

  int24(int value) : value_(value) {}
  int24() {}

  operator int() const { return value_; }
  operator=(int value) { value_ = value; }
};

enum { bit8 = 0x100,
       bit16 = bit8 * bit8,
       bit24 = bit8 * bit16,
       bit32 = bit8 * bit24,
       bit40 = bit8 * bit32,
       bit48 = bit8 * bit48,
       bit56 = bit8 * bit48 };

inline bool copy(int8 f, int8 *t) { *t = f; return true; }
inline bool copy(int8 f, int16 *t) { *t = f * bit8; return true; }
inline bool copy(int8 f, int24 *t) { *t = f * bit16; return true; }
inline bool copy(int8 f, int32 *t) { *t = f * bit24; return true; }
inline bool copy(int8 f, int64 *t) { *t = f * bit56; return true; }

inline bool copy(int16 f, int8 *t) { *t = f / bit8; return true; }
inline bool copy(int16 f, int16 *t) { *t = f; return true; }
inline bool copy(int16 f, int24 *t) { *t = f * bit8; return true; }
inline bool copy(int16 f, int32 *t) { *t = f * bit16; return true; }
inline bool copy(int16 f, int64 *t) { *t = f * bit48; return true; }

inline bool copy(int24 f, int8 *t) { *t = f / bit16; return true; }
inline bool copy(int24 f, int16 *t) { *t = f / bit8; return true; }
inline bool copy(int24 f, int24 *t) { *t = f; return true; }
inline bool copy(int24 f, int32 *t) { *t = f * bit8; return true; }
inline bool copy(int24 f, int64 *t) { *t = f * bit40; return true; }

inline bool copy(int32 f, int8 *t) { *t = f / bit24; return true; }
inline bool copy(int32 f, int16 *t) { *t = f / bit16; return true; }
inline bool copy(int32 f, int24 *t) { *t = f / bit8; return true; }
inline bool copy(int32 f, int32 *t) { *t = f; return true; }
inline bool copy(int32 f, int64 *t) { *t = f * bit32; return true; }

inline bool copy(int64 f, int8 *t) { *t = f / bit56; return true; }
inline bool copy(int64 f, int16 *t) { *t = f / bit48; return true; }
inline bool copy(int64 f, int24 *t) { *t = f / bit40; return true; }
inline bool copy(int64 f, int32 *t) { *t = f / bit32; return true; }
inline bool copy(int64 f, int64 *t) { *t = f; return true; }

}  // namespace persist
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FRAME__

#endif
