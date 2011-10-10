#include "rec/audio/source/Stretchy.h"
#include "rec/audio/stretch/AudioMagicStretchy.h"
#include "rec/audio/stretch/SoundTouchStretchy.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/util/Math.h"

using namespace juce;
using namespace google;

using rec::audio::stretch::Stretch;

namespace rec {
namespace audio {
namespace source {

Stretchy::Stretchy(Source* s, const Stretch& stretch) : Wrappy(s) {
  setStretch(stretch);
}

Stretchy::~Stretchy() {}

// static
Stretchy* Stretchy::create(Source* p, const Stretch& s) {
  switch (s.strategy()) {
   case Stretch::AUDIO_MAGIC: return stretch::createAudioMagicStretchy(p, s);
   case Stretch::SOUNDTOUCH: return stretch::createSoundTouchStretchy(p, s);
   default: return NULL;
  }
}

int64 Stretchy::getTotalLength() const {
  ScopedLock l(lock_);
  return scale(source()->getTotalLength());
}

int64 Stretchy::getNextReadPosition() const {
  ScopedLock l(lock_);
  return scale(source()->getNextReadPosition());
}

void Stretchy::setNextReadPosition(int64 position) {
  ScopedLock l(lock_);
  source()->setNextReadPosition(static_cast<int64>(position / timeScale_));
}

void Stretchy::setStretch(const stretch::Stretch& s) {
  ScopedLock l(lock_);
  stretch_ = s;

  static const double DELTA = 0.00001;
  timeScale_ = stretch::timeScale(stretch_);
  bypass_ = stretch_.passthrough_when_disabled() &&
    near(timeScale_, 1.0, DELTA) &&
    near(stretch::pitchScale(stretch_), 1.0, DELTA);
  channels_ = stretch_.channels();
  if (bypass_) {
    timeScale_ = 1.0;
    return;
  }

  if (!buffer_ || buffer_->getNumChannels() != channels_)
    buffer_.reset(new Buffer(channels_, SAMPLE_BUFFER_INITIAL_SIZE));

  outOffset_.resize(channels_);
  initializeStretcher();
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  DCHECK_EQ(info.buffer->getNumChannels(), channels_);
  bool bypass;
  {
    ScopedLock l(lock_);
    bypass = bypass_;
  }
  if (bypass)
    Wrappy::getNextAudioBlock(info);
  else
    doNextStretchedAudioBlock(info);
}

void Stretchy::doNextStretchedAudioBlock(const AudioSourceChannelInfo& info) {
  int zeroCount = 0;
  for (AudioSourceChannelInfo i = info; i.numSamples; ) {
    if (int processed = static_cast<int>(processOneChunk(i))) {
      if (zeroCount) {
        LOG_FIRST_N(ERROR, 20) << "Got it on try " << (zeroCount + 1);
      }

      i.numSamples -= processed;
      i.startSample += processed;
      zeroCount = 0;
    } else {
      CHECK_LT(++zeroCount, 10);
    }
  }
}

int64 Stretchy::processOneChunk(const AudioSourceChannelInfo& info) {
  int inSampleCount = getInputSampleCount(info.numSamples);
  buffer_->setSize(stretch_.channels(), inSampleCount, false, false, true);

  AudioSourceChannelInfo i;
  i.startSample = 0;
  i.numSamples = inSampleCount;
  i.buffer = buffer_.get();
  source()->getNextAudioBlock(i);

  for (int c = 0; c < channels_; ++c)
    outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

  return process(buffer_->getArrayOfChannels(), inSampleCount,
                 &outOffset_.front(), info.numSamples);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
