#include "rec/audio/source/TrackSource.h"
#include "rec/audio/source/BufferySourceFactory.h"

namespace rec {
namespace audio {
namespace source {

TrackSource::TrackSource(BufferySourceFactory* f, int offset)
    : factory_(f),
      offset_(offset),
      lock_(&f->lock()) {
}

void TrackSource::release() {
  ScopedLock l(*lock_);
  if (factory_) {
    factory_->removeSource(this);
    factory_ = NULL;
    myLock_.reset(new CriticalSection);
    lock_ = myLock_.get();
  }
}

void TrackSource::clearFactory() {
  ScopedLock l(*lock_);
  factory_ = NULL;
}

void TrackSource::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  ScopedLock l(*lock_);
  if (!factory_) {
    LOG(ERROR) << "Couldn't get audio block for deceased factory";
  } else {
    int len = getTotalLength();
    factory_->getAudioBlock(info, util::mod(offset_ + position_, len));
    position_ = util::mod(position_ + info.numSamples, len);
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
