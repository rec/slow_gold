#include <cmath>
#include "rec/util/Math.h"

#include "rec/gui/audio/LevelMeter.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

const float LevelMeter::SCALE_UP_METER = 2.0f;

LevelMeter::LevelMeter(bool horiz, bool rms, int margin)
    : horizontal_(horiz), rms_(rms), gain_(1.0f), margin_(margin) {
}

void LevelMeter::operator()(const LevelVector& levels) {
  {
    ScopedLock l(lock_);
    levels_ = levels;
    for (uint i = 0; i < levels_.size(); ++i) {
      // DCHECK(!std::isinf(levels_[i]));
      if (isinf(levels_[i]))
        levels_[i] = 1.0f;
      else if (isnan(levels_[i]))
        levels_[i] = 0.0f;
    }
  }
  thread::callAsync(this, &LevelMeter::repaint);
}

void LevelMeter::paint(Graphics& g) {
  g.fillAll(juce::Colours::white);

  ScopedLock l(lock_);
  int size = levels_.size();
  if (!size)
    return;

  float travel = static_cast<float>(horizontal_ ? getWidth() : getHeight());
  int width = (horizontal_ ? getHeight() : getWidth()) - (size - 1) * margin_;
  // TODO: I originally had int division on the next line, make sure the new code's right.
  float w = static_cast<float>(width) / size;

  juce::ColourGradient fill;
  fill.addColour(0.0, juce::Colours::green);
  fill.addColour(0.80, juce::Colours::yellow);
  fill.addColour(0.93, juce::Colours::red);

  fill.point1.setX(0.0);
  fill.point1.setY(0.0);
  fill.point2 = fill.point1;
  if (horizontal_)
    fill.point2.setX(travel);
  else
    fill.point2.setY(travel);
  g.setGradientFill(fill);

  for (int i = 0; i < size; ++i) {
    float w1 = ((width + margin_) * i) / size;
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
