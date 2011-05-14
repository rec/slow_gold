#ifndef __REC_GUI_AUDIO_LEVELMETER__
#define __REC_GUI_AUDIO_LEVELMETER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {
namespace audio {

class LevelMeter : public Component, public Listener<const vector<double>&> {
 public:
  LevelMeter(bool horizontal = true) : horizontal_(horizontal) {}

  virtual void operator()(const vector<double>& levels) {
    ScopedLock l(lock_);
    levels_ = levels;
  }

  virtual void paint(Graphics& g) {
    ScopedLock l(lock_);
    int size = levels_.size();
    float travel = horizontal_ ? getWidth() : getHeight();
    int width = horizontal_ ? getHeight() : getWidth();
    float w = width / size;
    for (int i = 0; i < size; ++i) {
      float t = travel * (levels_[i] + 1.0) / 2.0;
      float w1 = (width * i) / size;
      if (horizontal_)
        g.fillRect(0.0f, w1, t, w);
      else
        g.fillRect(w1, travel - t, w, t);
    }
  }

 private:
  CriticalSection lock_;
  vector<double> levels_;
  bool horizontal_;

  DISALLOW_COPY_AND_ASSIGN(LevelMeter);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LEVELMETER__
