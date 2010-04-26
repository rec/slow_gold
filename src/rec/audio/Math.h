#ifndef __REC_AUDIO_MATH
#define __REC_AUDIO_MATH

namespace rec {
namespace audio {
namespace math {

inline float rampWave(int ramp, int scale) {
  return ((ramp + scale) % (2 * scale + 1) - scale) / float(scale);
}

}  // namespace math
}  // namespace audio
}  // namespace rec


#endif  // __REC_AUDIO_MATH
