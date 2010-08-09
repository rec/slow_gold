#include <vector>

#include "rec/audio/stretch/Stretcher.h"

namespace rec {
namespace audio {
namespace timescaler {

AudioSampleBuffer* stretchOnce(const Description& description,
                               const AudioSampleBuffer& inbuf) {
  Description d(description);
  uint32 channels = std::min(d.channels(), (uint32) inbuf.getNumChannels());
  d.set_channels(channels);

  AudioTimeScaler scaler;
  Init(d, &scaler);

  int outSamples = inbuf.getNumSamples() * d.time_scale();
  AudioSampleBuffer* outbuf = new AudioSampleBuffer(channels, outSamples);

  CircularBuffer in(inbuf, 0);
  CircularBuffer out(*outbuf, 0);

  while (out.readFrom(d.chunk_size(), &in, &scaler));
  return outbuf;
}

}  // namespace timescaler
}  // namespace audio
}  // namespace rec
