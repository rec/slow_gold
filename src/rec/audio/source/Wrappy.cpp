#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Empty.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

Wrappy::Wrappy(PositionableAudioSource* s) : position_(0), prepared_(false) {
    setSource(s);
}

SampleTime Wrappy::mod(SampleTime x) const {
    Lock l(lock_);
    int64 length = getTotalLength();
    return length ? util::mod<int64>(x, length) : 0;
}

int64 Wrappy::getNextReadPosition() const {
    Lock l(lock_);
    return position_;
}

PositionableAudioSource* Wrappy::source() const {
    Lock l(lock_);
    if (PositionableAudioSource* source = getSource())
        return source;

    static Empty empty;
    return &empty;
}

void Wrappy::setSource(PositionableAudioSource* s) {
    Lock l(lock_);
    if (s != source_.get())
        source_.reset(s);
}

PositionableAudioSource* Wrappy::getSource() const {
    Lock l(lock_);
    return source_.get();
}

void Wrappy::swap(std::unique_ptr<PositionableAudioSource>* other) {
    Lock l(lock_);
    source_.swap(*other);
}

void Wrappy::prepareToPlay(int s, double r) {
    Lock l(lock_);

    source()->prepareToPlay(s, r);
    prepared_ = true;
}

void Wrappy::setNextReadPosition(int64 p) {
    Lock l(lock_);

    position_ = p;
    source()->setNextReadPosition(p);
}

void Wrappy::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
    Lock l(lock_);

    source()->getNextAudioBlock(info);
    position_ = mod(position_ + info.numSamples);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
