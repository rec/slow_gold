#ifndef __REC_GUI_AUDIO_LEVELMETER__
#define __REC_GUI_AUDIO_LEVELMETER__

#include "rec/util/listener/Listener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

class LevelMeter : public Component, 
                   public Listener<const LevelVector&> {
 public:
  LevelMeter(bool horizontal = true, bool rms = true)
      : horizontal_(horizontal), rms_(rms) {}

  virtual void operator()(const LevelVector& levels) {
    ScopedLock l(lock_);
    levels_ = levels;
    for (int i = 0; i < levels_.size(); ++i) {
      // DCHECK(!std::isinf(levels_[i]));
      if (std::isinf(levels_[i]))
        levels_[i] = 1.0;
      else if (std::isnan(levels_[i]))
        levels_[i] = 0.0;
    }
    thread::callAsync(this, &LevelMeter::repaint);
  }

  virtual void repaint() { Component::repaint(); }

  static const float SCALE_UP_METER = 1.7f;

  virtual void paint(Graphics& g) {
    g.fillAll(juce::Colours::white);

    ScopedLock l(lock_);
    int size = levels_.size();
    if (!size)
      return;

    float travel = horizontal_ ? getWidth() : getHeight();
    int width = horizontal_ ? getHeight() : getWidth();
    float w = width / size;

    for (int i = 0; i < size; ++i) {
      float w1 = (width * i) / size;
      if (rms_) {
        float t = travel * levels_[i] * SCALE_UP_METER;
        if (horizontal_)
          g.fillRect(0.0f, w1, t, w);
        else
          g.fillRect(w1, travel - t, w, t);
      }
    }
  }

 private:
  CriticalSection lock_;
  LevelVector levels_;
  bool horizontal_;
  bool rms_;

  DISALLOW_COPY_AND_ASSIGN(LevelMeter);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LEVELMETER__
