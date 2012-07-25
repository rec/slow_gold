#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Clear.h"
#include "rec/util/range/WrapSeries.h"
#include "rec/util/range/MakeRange.h"

namespace rec {
namespace audio {
namespace source {

void Selection::getNextAudioBlock(const juce::AudioSourceChannelInfo& audioInfo) {
  SampleRangeVector sel = selection();
  SampleTime pos = getNextReadPosition();
  if (!sel.begin()->end_) {
    clear(audioInfo);
    return;
  }
  AudioSourceChannelInfo info = audioInfo;
  SampleRangeVector blocks = fillSeries(sel, pos, SampleTime(info.numSamples), WRAP);

  for (SampleRangeVector::const_iterator i = blocks.begin(); i != blocks.end(); ++i) {
    setNextReadPosition(i->begin_);
    info.numSamples = static_cast<int>(i->size());
    Wrappy::getNextAudioBlock(info);
    info.startSample += info.numSamples;
  }
}

int64 Selection::getTotalLength() const {
  Lock l(lock_);
#ifdef CORRECT_SIZE_CALCULATIONS
  return block::getSize(selection_);
#else
  return Wrappy::getTotalLength();
#endif
}

int64 Selection::getCorrectTotalLength() const {
  Lock l(lock_);
  return makeRange<SampleTime>(selection_).size();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
