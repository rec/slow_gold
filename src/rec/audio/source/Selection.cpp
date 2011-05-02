#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Clear.h"

namespace rec {
namespace audio {
namespace source {

SampleTime Selection::getTotalLength() const {
  SampleTime time = 0;
  SampleSelection::const_iterator i;
  for (i = selection_.begin(); i != selection_.end(); ++i)
    time += i->size();
  return time;
}

void Selection::getNextAudioBlock(const juce::AudioSourceChannelInfo& audioInfo) {
  if (selection_.empty()) {
    LOG(ERROR) << "Tried to play an empty selection";
    clear(audioInfo);
    return;
  }

  AudioSourceChannelInfo info = audioInfo;
  int64 toCopy = info.numSamples;
  for (SampleSelection::iterator i = selection_.begin(); toCopy > 0; ++i) {
    if (i == selection_.end())
      i = selection_.begin();

    if (i->end_ > position_) {
      if (i->begin_ > position_)
        setNextReadPosition(i->begin_);
      info.numSamples = juce::jmin(toCopy, i->end_ - position_);
      Wrappy::getNextAudioBlock(info);

      info.startSample += info.numSamples;
      toCopy -= info.numSamples;
    }
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
