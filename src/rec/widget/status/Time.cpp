#include <math.h>
#include <glog/logging.h>

#include "rec/widget/status/Time.h"

#include "rec/gui/Color.h"

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

void TextComponent::setTimeSamples(int samples) {
  setTimeSeconds(samples / 44100.0);
}

void TextComponent::setTimeSeconds(float time) {
  setText(formatTime(time, description_.separator().flash()), false);
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

#ifdef _WIN32
#define snprintf _snprintf
#endif

  snprintf(buffer, 64, "%02d:%02d%c%02d.%03d",
           hours, minutes, ch, seconds, milliseconds);
  return buffer;
}

DialComponent::DialComponent(const Dial& desc)
    : Component(desc.widget().name().c_str()),
      description_(desc),
      time_(0) {
}

// Half a degree.
static const float ALMOST_ZERO = 0.5 / 360.0;

static const float PI = 3.1415926536;

void DialComponent::paint(Graphics& g) {
  Painter p(description_.widget(), &g);
  juce::Rectangle<int> bounds = p.getBounds(this);
  float zeroAngle = description_.zero_point() * 2.0 * PI;
  float timeAngle = zeroAngle + time_ * 2.0 * PI;
  if (p.colors().color_size() > 2) {
    g.setColour(p.colour(Painter::FOREGROUND).
                interpolatedWith(p.colour(Painter::HIGHLIGHT), time_));
  }

  Path path;
  path.addPieSegment(bounds.getX(), bounds.getY(),
                     bounds.getWidth(), bounds.getHeight(),
                     zeroAngle, timeAngle, 0);

  g.fillPath(path);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
