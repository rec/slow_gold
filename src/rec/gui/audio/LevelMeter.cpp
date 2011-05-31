#include "rec/gui/audio/LevelMeter.h"

namespace rec {
namespace gui {
namespace audio {

LevelMeter::LevelMeter(bool horiz, bool rms)
    : horizontal_(horiz), rms_(rms), gain_(1.0f) {
}

void LevelMeter::operator()(const LevelVector& levels) {
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

void LevelMeter::paint(Graphics& g) {
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
      float t = travel * gain_ * levels_[i] * SCALE_UP_METER;
      if (horizontal_)
        g.fillRect(0.0f, w1, t, w);
      else
        g.fillRect(w1, travel - t, w, t);
    }
  }
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
