#include <glog/logging.h>

#include "rec/audio/source/Buffery.h"
#include "rec/audio/CopySamples.h"
#include "rec/util/Math.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

using namespace rec::util::block;
using namespace rec::util::listener;
using namespace rec::util::thread;

namespace rec {
namespace audio {
namespace source {

Buffery::Buffery(PositionableAudioSource* source, int blockSize)
    : length_(source->getTotalLength()),
      buffer_(2, length_),
      position_(0),
      source_(source),
      blockSize_(blockSize) {
}

AudioSampleBuffer* Buffery::buffer() { return &buffer_; }

void Buffery::setPosition(int position) {
  ScopedLock l(lock_);
  position_ = position;
}

bool Buffery::hasFilled(Block b) const {
  ScopedLock l(lock_);
  if (b.second <= length_)
    return difference(filled_, b).empty();

  return hasFilled(Block(b.first, length_)) &&
    hasFilled(Block(0, b.second - length_));
}

bool Buffery::fill() {
  Block block(firstEmptyBlock());
  if (!getSize(b))
    return true;

  AudioSourceChannelInfo info;

  info.buffer = buffer_;
  info.startSample = block.first;
  info.numSamples = getSize(block);

  source_->setNextReadPosition(block.first);
  source_->getNextAudioBlock(info);

  ScopedLock l(lock_);
  merge(block, &filled_);
  return false;
}

Block Buffery::firstEmptyBlock(int p) const {
  ScopedLock l(lock_);
  return firstEmptyBlockAfter(filled_, p == -1 ? p : position_, length_);
}


#if 0

void fill(FilledBuffer* filledBuffer


void getAudioBlock(const Block& block, AudioSampleBuffer *buffer,
                   PositionableAudioSource* source) {
  source->setNextReadPosition(block.first);
  source->getNextAudioBlock(makeInfo(block, buffer));
}

// callback here.

void getAudioBlocks(const BlockSet blocks, AudioSampleBuffer *buffer,
                    PositionableAudioSource* source) {
  for (BlockSet::const_iterator i = block.begin(); i != blocks.end(); ++i)
    getAudioBlock(*i, buffer, source);
}

bool fillBlocksCovering(const Block& block, AudioSampleBuffer *buffer,
                        PositionableAudioSource* source) {

  if (isFull_)
    return true;

  BlockSet blocks = difference(filled_, block);
  for (BlockSet::iterator i = blocks.begin(); i != blocks.end(); ++i) {
    if (fill(*i)) {
      if (++i != blocks.end())
        LOG(ERROR) << "Ran out of space with blocks to fill.";
      return true;
    }
  }
  return false;
}

#ifdef USE_MALLOC_FOR_BUFFERY
#  define BUFFER_SIZE 0
#else
#  define BUFFER_SIZE length_
#endif

Buffery::Buffery(PositionableAudioSource* source, int blockSize)
    : source_(source),
      length_(source->getTotalLength()),
      buffer_(2, BUFFER_SIZE),
      isFull_(false),
      blockSize_(blockSize),
      position_(0) {
#ifdef USE_MALLOC_FOR_BUFFERY
  sampleData_[0] = (float*) malloc(sizeof(float) * length_);
  sampleData_[1] = (float*) malloc(sizeof(float) * length_);

  buffer_.setDataToReferTo(sampleData_, 2, length_);
#endif
}

Buffery::~Buffery() {
#ifdef USE_MALLOC_FOR_BUFFERY
  free(sampleData_[0]);
  free(sampleData_[1]);
#endif
}

void Buffer::setReadPosition(int p) {
  position_ = p;
  source_->setReadPosition(p);
}

bool Buffery::fill(const Block& block) {
  if (isFull_) {
    LOG(ERROR) << "Calling fill when isFull_";
    return true;
  }

  if (!getSize(block)) {
    LOG(ERROR) << "Calling fill for no data.";
    return false;
  }

  AudioSourceChannelInfo info;
  info.buffer = &buffer_;
  info.startSample = block.first;
  info.numSamples = getSize(block);
  return fill(block, info);
}

bool Buffery::fill(const Block& block,
                   const AudioSourceChannelInfo& info) {
  int length = getTotalLength();
  source_->setNextReadPosition(position_);
  source_->getNextAudioBlock(info);
  position_ = util::mod(position_ + info.numSamples, length);

  merge(block, &filled_);
  isFull_ = isBlock(filled_, Block(0, length));
  if (isFull_)
    broadcast(*this);

  return isFull_;
}

bool Buffery::fillBlocksCovering(const Block& block) {
  if (isFull_)
    return true;

  BlockSet blocks = difference(filled_, block);
  for (BlockSet::iterator i = blocks.begin(); i != blocks.end(); ++i) {
    if (fill(*i)) {
      if (++i != blocks.end())
        LOG(ERROR) << "Ran out of space with blocks to fill.";
      return true;
    }
  }
  return false;
}

bool Buffery::fillNextEmptyBlock() {
  return isFull_ ||
    fill(firstEmptyBlockAfter(filled_, position_, getTotalLength()));
}

void Buffery::ensureAudioBlock(const AudioSourceChannelInfo& info, int pos) {
  if (!isFull_) {
    size_t end = pos + info.numSamples;
    size_t length = getTotalLength();
    if (end <= length) {
      fillBlocksCovering(Block(pos, end));
    } else {
      fillBlocksCovering(Block(pos, length)) ||
        fillBlocksCovering(Block(0, end - length));
    }

    position_ = end;
  }
}

int Buffery::getAudioBlock(const AudioSourceChannelInfo& info, int position) {
  return rec::audio::copyCircularSamples(buffer_, position, info);
}
#endif
}  // namespace source
}  // namespace audio
}  // namespace rec
