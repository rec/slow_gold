#pragma once

#include "rec/app/LanguageListener.h"
#include "rec/audio/Audio.h"
#include "rec/audio/util/Gain.h"
#include "rec/util/Disableable.h"
#include "rec/util/Listener.h"
#include "rec/util/StateListener.h"

namespace rec {
namespace gui {
namespace audio {

class LevelMeter : public Component,
                                      public app::LanguageListener,
                                      public Disableable,
                                      public Listener<const rec::audio::Gain&>,
                                      public StateListener<const rec::audio::LevelVector&>,
                                      public SettableTooltipClient {
  public:
    LevelMeter(const string& name, const string& tooltip,
                          bool horizontal = true, bool rms = true, int margin = 2);

    void operator()(const rec::audio::LevelVector&) override;
    void operator()(const rec::audio::Gain&) override;

    void languageChanged() override;
    void paint(Graphics& g) override;
    void repaint() { Component::repaint(); }

    static const float SCALE_UP_METER;

  private:
    CriticalSection lock_;
    string tooltip_;
    rec::audio::LevelVector levels_;
    bool horizontal_;
    bool rms_;
    float gain_;
    int margin_;
    bool preFaderLevels_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(LevelMeter);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

