#ifndef __REC_AUDIO_UTIL_FRAME__
#define __REC_AUDIO_UTIL_FRAME__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample = short, int CHANNELS = 2>
struct Frame  {
  Sample sample_[CHANNELS];
};

template <typename From, typename To> void convert(From f, To* t) { *t = f; }

static const double NEG_RANGE = 32768.0;
static const double FULL_RANGE = 2.0 * NEG_RANGE - 2;

inline void convert(float from, short* to) {
  *to = static_cast<short>(FULL_RANGE * (1.0 + from) / 2.0 - NEG_RANGE);
}

inline void convert(short from, float* to) {
  *to = 2.0 * (from + NEG_RANGE) / FULL_RANGE - 1.0;
}

template <typename Sample = short, int CHANNELS = 2>
struct Frames : public vector< Frame<Sample, CHANNELS> > {
  typedef vector< Frame<Sample, CHANNELS> > super;

  Frames() {}
  Frames(SampleTime n) : super(n) {}
  Frames(SampleTime n, const Frame<Sample, CHANNELS>& f) : super(n, f) {}

  template <typename Sample2>
  void copyFrom(SampleTime nsamples, SampleTime beginTo, SampleTime beginFrom,
                const Frames<Sample2, CHANNELS>& from) {
    nsamples = std::min(nsamples, this->size() - beginTo);
    nsamples = std::min(nsamples, from->size() - beginFrom);

    for (int i = 0; i < nsamples; ++i)
      convert(from[i + beginTo], &(*this)[i + beginTo]);
  }

  template <typename Iter> Frames(Iter b, Iter e) : super(b, e) {}
};


}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FRAME__
