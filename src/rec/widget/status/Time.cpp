#include <math.h>

#include "rec/widget/status/Time.h"
#include "rec/util/FormatTime.h"
#include "rec/util/Math.h"
#include "rec/gui/Color.h"
#include "rec/gui/Geometry.h"
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
    : gui::SimpleLabel(desc.widget().name().c_str()),
      description_(desc) {
  setJustificationType(juce::Justification::centred);
  setFont(Font(juce::Font::getDefaultMonospacedFontName(), 20, Font::plain));
}

void TextComponent::setTime(double time) {
  time_ = time;
  thread::callAsync(this, &TextComponent::redisplay);
}

void TextComponent::operator()(const ClockUpdate& c) {
  if (c.time_ >= 0)
    setTime(c.time_);
}

void TextComponent::redisplay() {
  setText(formatTime(time_, description_.separator().flash()), false);
}


DialComponent::DialComponent(const Dial& desc, double length, double time)
    : gui::CuttableComponent(desc.widget().name().c_str()),
      description_(desc),
      length_(length),
      time_(time) {
}

// Half a degree.
static const double ALMOST_ZERO = 0.5 / 360.0;

static const double PI = 3.1415926536;

void DialComponent::paint(Graphics& g) {
  ScopedLock l(lock_);
  double timeRatio = Math<double>::near(length_, 0.0f, 0.001f) ? 0.0f : (time_ / length_);
  Painter p(description_.widget(), &g);
  juce::Rectangle<int> bounds = gui::centerSquare(p.getBounds(this));
  double zeroAngle = description_.zero_point() * 2.0 * PI;
  double timeAngle = zeroAngle + timeRatio * 2.0 * PI;
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

void DialComponent::setTime(double time) {
  ScopedLock l(lock_);
  time_ = time;
  thread::callAsync(this, &DialComponent::repaint);
}

void DialComponent::setLength(double length) {
  ScopedLock l(lock_);
  length_ = length;
  thread::callAsync(this, &DialComponent::repaint);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
