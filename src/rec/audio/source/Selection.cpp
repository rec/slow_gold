#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Clear.h"
#include "rec/util/block/FillSeries.h"

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
  BlockList blocks = fillSeries(selection_, position_, info.numSamples);
  
  for (BlockList::const_iterator i = blocks.begin(); i != blocks.end(); ++i) {
    setNextReadPosition(i->first);
    info.numSamples = getSize(*i);
    Wrappy::getNextAudioBlock(info);
    info.startSample += info.numSamples;
  }
}

void Selection::setSelection(const BlockSet& s) {
  ScopedLock l(lock_);
  selection_ = s;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
