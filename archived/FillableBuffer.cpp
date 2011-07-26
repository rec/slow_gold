#include "rec/audio/util/FillableBuffer.h"
#include "rec/audio/util/CopySamples.h"
#include "rec/base/SamplePosition.h"
#include "rec/util/Math.h"
#include "rec/util/block/Block.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

using namespace rec::util::block;

namespace rec {
namespace audio {
namespace util {

void FillableBuffer::setSource(PositionableAudioSource* source) {
  setLength(source->getTotalLength());
  buffer_.reset(new AudioSampleBuffer(2, length_));
  source_.reset(source);
}

block::Size FillableBuffer::doFillNextBlock(const Block& block) {
  AudioSourceChannelInfo info;
  info.buffer = buffer_.get();
  info.startSample = block.first;
  info.numSamples = juce::jmin(getSize(block), static_cast<block::Size>(blockSize_));

  source_->setNextReadPosition(block.first);
  source_->getNextAudioBlock(info);

  return info.numSamples;
}

}  // namespace util
}  // namespace audio
}  // namespace rec
