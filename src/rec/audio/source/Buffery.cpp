#include "rec/audio/source/Buffery.h"
#include "rec/audio/CopySamples.h"
#include "rec/util/Math.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

using namespace rec::util::block;
using namespace rec::util::listener;

namespace rec {
namespace audio {
namespace source {

Buffery::Buffery(PositionableAudioSource* source, int blockSize)
    : Filler(source->getTotalLength(), blockSize),
      buffer_(2, length_),
      source_(source) {
}

void Buffery::doFillNextBlock(const Block& b) {
	Block block = b;
  AudioSourceChannelInfo info;
  info.buffer = &buffer_;
  info.startSample = block.first;
  info.numSamples = juce::jmin(getSize(block), static_cast<block::Size>(blockSize_));
  block.second = block.first + info.numSamples;

  source_->setNextReadPosition(block.first);
  source_->getNextAudioBlock(info);

  ScopedLock l(lock_);
  merge(block, &filled_);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
