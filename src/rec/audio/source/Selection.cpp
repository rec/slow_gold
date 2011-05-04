#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Clear.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::util::block;

void Selection::getNextAudioBlock(const juce::AudioSourceChannelInfo& audioInfo) {
  BlockSet selection;
  {
    ScopedLock l(lock_);
    selection = selection_;
  }

  if (selection.empty()) {
    LOG(ERROR) << "Tried to play an empty selection";
    clear(audioInfo);
    return;
  }

  AudioSourceChannelInfo info = audioInfo;
  int64 toCopy = info.numSamples;
  for (BlockSet::iterator i = selection.begin(); toCopy > 0; ++i) {
    bool isEnd = (i == selection.end());
    if (isEnd || i->second > position_) {
      if (isEnd)
        i = selection.begin();
      if (isEnd || i->first > position_)
        setNextReadPosition(i->first);
      info.numSamples = juce::jmin(toCopy, i->second - position_);
      Wrappy::getNextAudioBlock(info);

      info.startSample += info.numSamples;
      toCopy -= info.numSamples;
    }
  }
}

void Selection::setSelection(const BlockSet& s) {
  ScopedLock l(lock_);
  selection_ = s;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
