#ifndef __REC_AUDIO_UTIL_FRAME__
#define __REC_AUDIO_UTIL_FRAME__

#include "rec/base/SamplePosition.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
struct Frame  {
  Sample sample_[CHANNELS];
};

// template <typename From, typename To> void convert(From f, To* t) { *t = f; }

template <typename Sample, int CHANNELS>
struct Frames : public vector< Frame<Sample, CHANNELS> > {
  typedef vector< Frame<Sample, CHANNELS> > super;

  Frames() {}
  Frames(SamplePosition n) : super(n) {}
  Frames(SamplePosition n, const Frame<Sample, CHANNELS>& f) : super(n, f) {}

  template <typename Sample2>
  void copyFrom(SamplePosition nsamples, SamplePosition beginTo, SamplePosition beginFrom,
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
