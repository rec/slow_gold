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

void Selection::onDataChange(const LoopPointList& loops) {
  Lock l(Wrappy::lock_);
  selection_ = getTimeSelection(loops);
  if (selection_.empty())
    selection_.insert(block::makeBlock(0, Samples<44100>(RealTime(loops.length()))));
}

void Selection::moveBackward(Samples<44100> dt) {
  Lock l(Wrappy::lock_);
  BlockSet sel = selection();
  if (!sel.begin()->second) {
    return;
  }
  BlockSet::const_iterator i = sel.begin();
  for (; i != sel.end() && i->second <= position_; ++i);
  if (i == sel.end())
    --i;

  for (; dt > 0; --i) {
    position_ = std::min<int64>(position_, i->second);
    Samples<44100> moved = std::min<int64>(position_ - i->first, dt);
    DCHECK(moved);
    dt -= moved;
    position_ -= moved;
    if (dt > 0 && i == sel.begin()) {
      i = sel.end();
      position_ = getTotalLength();
    }
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
