#include "rec/audio/source/TrackSource.h"

namespace rec {
namespace audio {
namespace source {

typedef BufferySourceFactory::SourceSet SourceSet;

TrackSource::TrackSource(BufferySourceFactory* f, int offset)
    : Wrappy::Position(NULL),
      factory_(f),
      offset_(offset),
      lock_(&f->lock_) {
}

void TrackSource::release() {
  ScopedLock l(*lock_);
  if (factory_) {
    factory_->sources_->remove(this);
    myLock_.reset(new CriticalSection);
    lock_ = myLock.get();
    factory_ = NULL;
  }
}

void TrackSource::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  ScopedLock l(*lock_);
  if (!factory_) {
    LOG(ERROR) << "Couldn't get audio block for deceased factory";
  } else {
    factory_->getAudioBlock(info, factory_->mod(offset_ + position_));
    position_ = factory->mod(position_ + info.numSamples);
  }
}

int TrackSource::getTotalLength() const {
  ScopedLock l(*lock_);
  return factory_ ? factory_->getTotalLength() : 0;
}

int TrackSource::getNextReadPosition() const {
  ScopedLock l(*lock_);
  return position_;
}

void TrackSource::setNextReadPosition(int p) {
  ScopedLock l(*lock_);
  if (factory_)
    factory_->setReadPosition(p);
  position_ = p;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
