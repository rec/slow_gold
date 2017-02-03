#pragma once

#include "rec/audio/Audio.h"
#include "rec/base/SampleRate.h"
#include "rec/audio/stretch/Implementation.h"
#include "rec/audio/stretch/Stretch.h"

namespace RubberBand { class RubberBandStretcher; }

namespace rec {
namespace audio {
namespace stretch {

typedef ::RubberBand::RubberBandStretcher RubberBandStretcher;

class RubberBand : public Implementation {
  public:
    explicit RubberBand(Source* source,
                        const StretchParameters& stretch =
                        StretchParameters::default_instance());
    virtual ~RubberBand();

    virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);
    virtual bool canBypass() const;

    virtual void init();

  private:
    virtual void stretchChanged();

    std::unique_ptr<RubberBandStretcher> stretcher_;

    SampleRate outputSampleRate_;
    double timeScale_;
    double pitchScale_;

    int retrieve(int copied, const AudioSourceChannelInfo&);
    void process();

    DISALLOW_COPY_ASSIGN_AND_LEAKS(RubberBand);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec
