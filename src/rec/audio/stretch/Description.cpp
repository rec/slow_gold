#include <vector>

#include "juce_amalgamated.h"
#include "rec/audio/stretch/Description.h"
#include "rec/util/Math.h"


namespace rec {
namespace audio {
namespace stretch {

Range<float**> makeRange(const AudioSampleBuffer& b) {
  Range<float**> r;
  r.begin_ = b.getSampleData();
  r.end_ = r.begin_ + b.numChannels();
  return r;
};

Description<float*> makeDescriptionAndResize(
    const TimeScalerDescription& timescale,
    const AudioBuffer& inBuf,
    int inPosition,
    int inSize,
    AudioBuffer* outBuf) {
  Description<float*> desc;
  desc.timescale_ = timescale;

  CircularSamples<float*>& in = desc_.in_;
  CircularSamples<float*>& out = desc_.out_;

  Circular& inc = in.circular_;
  Circular& outc = out.circular_;

  inc.position_ = inPosition;
  inc.size_ = inSize;

  outc = inc;
  outc.scale(timescale.timescale_);

  outBuf->setSize(in.samples_.length(), outc.size_);

  in.samples_ = makeRange(inBuf);
  out.samples_ = makeRange(*outBuf);

  return desc;
}

Description<float*> makeDescription(const TimeScalerDescription& timescale,
                                    int inPosition,
                                    int inSize) {
  Description<float*> desc;
  desc.timescale_ = timescale;

  CircularSamples<float*>& in = desc_.in_;
  CircularSamples<float*>& out = desc_.out_;

  Circular& inc = in.circular_;
  Circular& outc = out.circular_;

  inc.position_ = inPosition;
  inc.size_ = inSize;

  outc = inc;
  outc.scale(timescale.timescale_);

  return desc;
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
