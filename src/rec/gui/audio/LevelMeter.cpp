#include <cmath>
#include "rec/util/Math.h"

#include "rec/gui/audio/LevelMeter.h"
#include "rec/audio/util/Gain.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

// Skin
const float LevelMeter::SCALE_UP_METER = 2.0f;
static const float GAP_WIDTH = 2.0f;
static const int SEGMENT_COUNT = 32;

LevelMeter::LevelMeter(bool horiz, bool rms, int margin)
    : horizontal_(horiz),
      rms_(rms),
      gain_(1.0f),
      margin_(margin),
      preFaderLevels_(false) {
}

void LevelMeter::operator()(const rec::audio::LevelVector& levels) {
  {
    Lock l(lock_);
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

  Lock l(lock_);
  int size = levels_.size();
  if (!size)
    return;

  float travel = static_cast<float>(horizontal_ ? getWidth() : getHeight());
  float base = static_cast<float>(horizontal_ ? getHeight() : getWidth());
  float adjustedBase = base - (size - 1) * margin_;
  float w = adjustedBase / size;

  juce::ColourGradient fill;
  fill.isRadial = false;
  fill.addColour(0.0, juce::Colours::green);
  fill.addColour(0.80, juce::Colours::yellow);
  fill.addColour(0.93, juce::Colours::red);

  fill.point1.setX(0.0f);
  fill.point1.setY(0.0f);
  fill.point2 = fill.point1;
  if (horizontal_)
    fill.point2.setX(travel);
  else
    fill.point2.setY(travel);
  g.setGradientFill(fill);

  for (int i = 0; i < size; ++i) {
    float w1 = ((adjustedBase + margin_) * i) / size;
    if (rms_) {
      float gain = preFaderLevels_ ? 1.0f : gain_;
      float t = travel * gain * levels_[i] * SCALE_UP_METER;
      if (horizontal_)
        g.fillRect(0.0f, w1, t, w);
      else
        g.fillRect(w1, travel - t, w, t);
    }
  }

  g.setColour(juce::Colours::white);

  float spacing = travel / SEGMENT_COUNT;
  for (int i = 1; i < SEGMENT_COUNT; ++i) {
    float pos = spacing * i - GAP_WIDTH / 2;
    if (horizontal_)
      g.fillRect(pos, 0.0f, GAP_WIDTH, base);
    else
      g.fillRect(0.0f, pos, base, GAP_WIDTH);
  }
}

void LevelMeter::operator()(const rec::audio::Gain& gain) {
  Lock l(lock_);
  gain_ = static_cast<float>(getGain(gain));
  preFaderLevels_ = gain.prefader_levels();
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
