#ifndef __REC_GUI_AUDIO_LEVELMETER__
#define __REC_GUI_AUDIO_LEVELMETER__

#include "rec/app/LanguageListener.h"
#include "rec/audio/Audio.h"
#include "rec/audio/util/Gain.h"
#include "rec/util/Listener.h"

namespace rec {
namespace gui {
namespace audio {

class LevelMeter : public Component,
                   public app::LanguageListener,
                   public Listener<const rec::audio::Gain&>,
                   public Listener<const rec::audio::LevelVector&>,
                   public SettableTooltipClient {
 public:
  LevelMeter(const string& name, const string& tooltip,
             bool horizontal = true, bool rms = true, int margin = 2);

  virtual void operator()(const rec::audio::LevelVector&);
  virtual void operator()(const rec::audio::Gain&);
  virtual void repaint() { Component::repaint(); }

  virtual void languageChanged();

  static const float SCALE_UP_METER;

  virtual void paint(Graphics& g);

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

#endif  // __REC_GUI_AUDIO_LEVELMETER__
