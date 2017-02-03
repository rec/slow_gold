#pragma once

#include "rec/audio/Audio.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/base/SampleRate.h"

namespace rec {
namespace audio {
namespace stretch {

class Implementation {
  public:
    static const int INITIAL_BUFFER_SIZE = (1 << 14);

    explicit Implementation(Source* s,
                            const StretchParameters& stretch =
                            StretchParameters::default_instance());
    virtual ~Implementation() {}

    virtual void getNextAudioBlock(const AudioSourceChannelInfo&) = 0;
    virtual void init() = 0;

    void setStretch(const Stretch&);
    void setMasterTune(double);
    void setInputSampleRate(SampleRate);
    void setOutputSampleRate(SampleRate);

    virtual bool canBypass() const = 0;
    double timeScale() const;
    double pitchScale() const;

    const StretchParameters stretch() const {
        Lock l(lock_);
        return stretch_;
    }

  protected:
    virtual void stretchChanged() = 0;

    float** getSourceSamples(int);

    CriticalSection lock_;
    StretchParameters stretch_;

  private:
    PositionableAudioSource* source_;
    AudioSampleBuffer buffer_;
    AudioSourceChannelInfo info_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(Implementation);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec
