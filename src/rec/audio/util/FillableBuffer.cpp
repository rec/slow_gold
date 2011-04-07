#include "rec/audio/util/FillableBuffer.h"
#include "rec/audio/util/CopySamples.h"
#include "rec/util/Math.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

using namespace rec::util::block;

namespace rec {
namespace audio {

FillableBuffer::FillableBuffer(PositionableAudioSource* source, int blockSize)
    : Filler(source->getTotalLength(), blockSize),
      buffer_(2, length_),
      source_(source) {
  DLOG(INFO) << "FillableBuffer: " << &buffer_;
}

block::Size FillableBuffer::doFillNextBlock(const Block& block) {
  // DLOG(INFO) << "doFillNextBlock: " << block.first << ", " << getSize(block);

  AudioSourceChannelInfo info;
  info.buffer = &buffer_;
  info.startSample = block.first;
  info.numSamples = juce::jmin(getSize(block), static_cast<block::Size>(blockSize_));

  source_->setNextReadPosition(block.first);
  source_->getNextAudioBlock(info);

  return block.first + info.numSamples;
}

}  // namespace audio
}  // namespace rec
