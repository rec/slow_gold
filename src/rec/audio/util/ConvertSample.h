#ifndef __REC_AUDIO_UTIL_CONVERTSAMPLE__
#define __REC_AUDIO_UTIL_CONVERTSAMPLE__

#include "rec/base/base.h"

namespace rec {
namespace audio {

enum { bit8 = 0x100,
       bit16 = bit8 * bit8,
       bit24 = bit8 * bit16,
       bit32 = bit8 * bit24,
       bit40 = bit8 * bit32,
       bit48 = bit8 * bit48,
       bit56 = bit8 * bit48 };

inline void convertSample(int8 f, int8 *t) { *t = f; }
inline void convertSample(int8 f, int16 *t) { *t = f * bit8; }
inline void convertSample(int8 f, int24 *t) { *t = f * bit16; }
inline void convertSample(int8 f, int32 *t) { *t = f * bit24; }
inline void convertSample(int8 f, int64 *t) { *t = f * bit56; }

inline void convertSample(int16 f, int8 *t) { *t = f / bit8; }
inline void convertSample(int16 f, int16 *t) { *t = f; }
inline void convertSample(int16 f, int24 *t) { *t = f * bit8; }
inline void convertSample(int16 f, int32 *t) { *t = f * bit16; }
inline void convertSample(int16 f, int64 *t) { *t = f * bit48; }

inline void convertSample(int24 f, int8 *t) { *t = f / bit16; }
inline void convertSample(int24 f, int16 *t) { *t = f / bit8; }
inline void convertSample(int24 f, int24 *t) { *t = f; }
inline void convertSample(int24 f, int32 *t) { *t = f * bit8; }
inline void convertSample(int24 f, int64 *t) { *t = f * bit40; }

inline void convertSample(int32 f, int8 *t) { *t = f / bit24; }
inline void convertSample(int32 f, int16 *t) { *t = f / bit16; }
inline void convertSample(int32 f, int24 *t) { *t = f / bit8; }
inline void convertSample(int32 f, int32 *t) { *t = f; }
inline void convertSample(int32 f, int64 *t) { *t = f * bit32; }

inline void convertSample(int64 f, int8 *t) { *t = f / bit56; }
inline void convertSample(int64 f, int16 *t) { *t = f / bit48; }
inline void convertSample(int64 f, int24 *t) { *t = f / bit40; }
inline void convertSample(int64 f, int32 *t) { *t = f / bit32; }
inline void convertSample(int64 f, int64 *t) { *t = f; }

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_CONVERTSAMPLE__
