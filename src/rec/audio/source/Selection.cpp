#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Clear.h"
#include "rec/util/block/FillSeries.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::util::block;

void Selection::getNextAudioBlock(const juce::AudioSourceChannelInfo& audioInfo) {
  BlockSet sel = selection();
  Samples<44100> pos = getNextReadPosition();
  if (!sel.begin()->second) {
    clear(audioInfo);
    return;
  }
  AudioSourceChannelInfo info = audioInfo;
  BlockList blocks = wrapSeries(sel, pos, info.numSamples);

  for (BlockList::const_iterator i = blocks.begin(); i != blocks.end(); ++i) {
    setNextReadPosition(i->first);
    info.numSamples = static_cast<int>(getSize(*i));
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

}  // namespace source
}  // namespace audio
}  // namespace rec
