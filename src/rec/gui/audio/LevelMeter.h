#ifndef __REC_GUI_AUDIO_LEVELMETER__
#define __REC_GUI_AUDIO_LEVELMETER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {
namespace audio {

class LevelMeter : public Component,
                   public Listener<const LevelVector&> {
 public:
  LevelMeter(bool horizontal = true, bool rms = true, int margin = 2);

  virtual void operator()(const LevelVector& levels);
  virtual void repaint() { Component::repaint(); }

  static const float SCALE_UP_METER;

  virtual void paint(Graphics& g);
  void setGain(float g) { ScopedLock l(lock_); gain_ = g; }
  void setPreFaderLevels(bool p) { Lock l(lock_); preFaderLevels_ = p; }

 private:
  CriticalSection lock_;
  LevelVector levels_;
  bool horizontal_;
  bool rms_;
  float gain_;
  int margin_;
  bool preFaderLevels_;

  DISALLOW_COPY_AND_ASSIGN(LevelMeter);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LEVELMETER__
