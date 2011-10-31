#include "rec/audio/stretch/SoundTouchStretchy.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/soundtouch/SoundTouch.h"

namespace rec {
namespace audio {
namespace stretch {

using soundtouch::SoundTouch;

namespace {

class SoundTouchStretchy : public Stretchy {
 public:
  static const int INPUT_BUFFER_SAMPLES = 4096;

  SoundTouchStretchy(PositionableAudioSource* s, const Stretch& stretch)
      : Stretchy(s, stretch), buffer_(2, INPUT_BUFFER_SAMPLES) {
    fetchInfo_.numSamples = INPUT_BUFFER_SAMPLES;
    fetchInfo_.startSample = 0;
    fetchInfo_.buffer = &buffer_;
    frames_.setLength(INPUT_BUFFER_SAMPLES);
  }
  virtual ~SoundTouchStretchy() {}

  void initializeStretcher() {
    soundTouch_.reset(new SoundTouch);
    soundTouch_->setRate(static_cast<float>(timeScale(stretch_)));
    soundTouch_->setChannels(stretch_.channels());
    soundTouch_->setPitch(pitchScale(stretch_));
  }

 protected:
  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo& info) {
    fillInput(info.numSamples);
    copyToOutput(info);
  }

  bool fillInput(int numSamples) {
    static const int MAXIMUM_FAILURE_COUNT = 10;
    for (int fail = 0, s; (s = soundTouch_->numSamples()) && s < numSamples; ) {
      putSamples(fetchInfo_);
      if (s == soundTouch_->numSamples()) {
        if (++fail > MAXIMUM_FAILURE_COUNT) {
          LOG(ERROR) << "Made no progress in pitch shifter";
          return false;
        }
      } else {
        fail = 0;
      }
    }
    return true;
  }

  void putSamples(const AudioSourceChannelInfo& info) {
    Stretchy::getNextAudioBlock(info);
    FloatFrame* frame = frames_.frames();
    for (int i = 0; i < info.numSamples; ++i, ++frame) {
      for (int c = 0; c < 2; ++c)
        frame->sample_[c] = *buffer_.getSampleData(c, i);
    }

    soundTouch_->putSamples(frames_.frames()->sample_, info.numSamples);
  }

  void copyToOutput(const AudioSourceChannelInfo& info) {
    int n = info.numSamples;
    if (frames_.length() < n)
      frames_.setLength(n);
    uint rec = soundTouch_->receiveSamples(frames_.frames()->sample_, n);

    if (static_cast<int>(rec) != n)
      LOG(ERROR) << "Expected " << n << " got " << rec;

    FloatFrame* frame = frames_.frames();
    for (int i = 0; i < n; ++i, ++frame) {
      for (int c = 0; c < 2; ++c)
        *info.buffer->getSampleData(c, i) = frame->sample_[c];
    }
  }

 private:
  Frames<FloatFrame> frames_;

  ptr<SoundTouch> soundTouch_;
  AudioSampleBuffer buffer_;

  AudioSourceChannelInfo fetchInfo_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SoundTouchStretchy);
};

}  // namespace

Stretchy* createSoundTouchStretchy(PositionableAudioSource* p,
                                           const Stretch& s) {
  return new SoundTouchStretchy(p, s);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

