#include <math.h>

#include "rec/widget/status/Time.h"
#include "rec/util/Math.h"
#include "rec/gui/Color.h"
#include "rec/widget/Painter.h"
#include "rec/util/thread/CallAsync.h"

using rec::gui::Colors;
using rec::gui::Color;

using namespace juce;

namespace rec {
namespace widget {
namespace status {
namespace time {

TextComponent::TextComponent(const Text& desc)
    : Label(desc.widget().name().c_str()),
      description_(desc) {
}

void TextComponent::setTime(float time) {
  time_ = time;
  thread::callAsync(this, &TextComponent::redisplay);
}

void TextComponent::redisplay() {
  setText(formatTime(time_, description_.separator().flash()), false);
}

#ifdef _WIN32
#define snprintf _snprintf
#endif

const String formatTime(float time, bool flash) {
  int seconds = time;
  float fraction = time - seconds;
  int milliseconds = 1000 * fraction;
  // int frames = 75 * fraction;

  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  char buffer[64];
  char ch = ':';
  if (flash && (seconds & 1))
    ch = ' ';

  snprintf(buffer, 64, "%02d:%02d%c%02d.%03d",
           hours, minutes, ch, seconds, milliseconds);
  return buffer;
}

DialComponent::DialComponent(const Dial& desc, float length, float time)
    : Component(desc.widget().name().c_str()),
      description_(desc),
      length_(length),
      time_(time) {
}

// Half a degree.
static const float ALMOST_ZERO = 0.5 / 360.0;

static const float PI = 3.1415926536;

void DialComponent::paint(Graphics& g) {
  ScopedLock l(lock_);
  float timeRatio = Math<float>::near(length_, 0.0f, 0.001f) ? 0.0f : (time_ / length_);
  Painter p(description_.widget(), &g);
  juce::Rectangle<int> bounds = p.getBounds(this);
  float zeroAngle = description_.zero_point() * 2.0 * PI;
  float timeAngle = zeroAngle + timeRatio * 2.0 * PI;
  if (p.colors().color_size() > 2) {
    g.setColour(p.colour(Painter::FOREGROUND).
                interpolatedWith(p.colour(Painter::HIGHLIGHT), timeRatio));
  }

  Path path;
  path.addPieSegment(bounds.getX(), bounds.getY(),
                     bounds.getWidth(), bounds.getHeight(),
                     zeroAngle, timeAngle, 0);

  g.fillPath(path);
}

void DialComponent::setTime(float time) {
  ScopedLock l(lock_);
  time_ = time;
  thread::callAsync(this, &DialComponent::repaint);
}

void DialComponent::setLength(float length) {
  ScopedLock l(lock_);
  length_ = length;
  thread::callAsync(this, &DialComponent::repaint);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
