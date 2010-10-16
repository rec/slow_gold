#include <math.h>
#include <glog/logging.h>

#include "rec/widget/Time.h"

#include "rec/gui/Color.h"
#include "rec/gui/Font.h"

#include "JuceLibraryCode/JuceHeader.h"

using rec::gui::Colors;
using rec::gui::Color;

using namespace juce;

namespace rec {
namespace widget {
namespace time {

TextComponent::TextComponent(const Text& desc)
    : WidgetBase<Component, Text>(desc),
      time_(0) {
}

void TextComponent::setTimeSamples(int samples) {
  setTimeSeconds(samples / SAMPLES_PER_SECOND);
}

void TextComponent::setTimeSeconds(float time) {
  time_ = time;
  repaint();
}

#ifdef _WIN32
#define snprintf snprintf_s
#endif

void TextComponent::paint(Graphics& g, const Rectangle<int>& bounds) {
  int seconds = time_;
  float fraction = time_ - seconds;
  int milliseconds = 1000 * fraction;
  // int frames = 75 * fraction;

  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  char buffer[64];
  char ch = ':';
  if (desc_.separator().flash() && (seconds & 1))
    ch = ' ';
  snprintf(buffer, 64, "%02d:%02d%c%02d.%03d",
          hours, minutes, ch, seconds, milliseconds);
  int margin = desc_.widget().margin();
  g.drawSingleLineText(buffer, margin, font().getAscent() + margin);
}

DialComponent::DialComponent(const Dial& desc)
    : WidgetBase<Component, Dial>(desc), time_(0) {
}

// Half a degree.
static const float ALMOST_ZERO = 0.5 / 360.0;

static const float PI = 3.1415926536;

void DialComponent::paint(Graphics& g, const Rectangle<int>& bounds) {
  float zeroAngle = desc_.zero_point() * 2.0 * PI;
  float timeAngle = zeroAngle + time_ * 2.0 * PI;
  if (colors().color_size() > 2)
    g.setColour(colour(1).interpolatedWith(colour(2), time_));

  Path path;
  path.addPieSegment(bounds.getX(), bounds.getY(),
                     bounds.getWidth(), bounds.getHeight(),
                     zeroAngle, timeAngle, 0);

  g.fillPath(path);
}

}  // namespace time
}  // namespace widget
}  // namespace rec
