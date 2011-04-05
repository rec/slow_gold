#include <math.h>

#include "rec/widget/status/DialComponent.h"
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

// Half a degree.
static const double ALMOST_ZERO = 0.5 / 360.0;

const double DialComponent::PI = 3.14159265358979323846264;
const double DialComponent::REDRAW_ANGLE = 2.0 * DialComponent::PI * 0.001;
const double SMALLEST_REAL_LENGTH = 0.01;

DialComponent::DialComponent(const Dial& desc, double length, double time)
    : Component(desc.widget().name().c_str()),
      description_(desc),
      length_(length),
      time_(time),
      range_(0.0, 0.0),
      zeroAngle_(0.0),
      timeAngle_(0.0),
      timeRatio_(0.0)
 {
}

void DialComponent::setTime(double time) {
  ScopedLock l(lock_);
  time_ = time;
  recomputeAngle();
}

void DialComponent::setLength(double length) {
  ScopedLock l(lock_);
  length_ = length;
  recomputeAngle();
}

void DialComponent::operator()(const SelectionRange& c) {
  ScopedLock l(lock_);
  range_ = TimeRange(c);
  recomputeAngle();
}

void DialComponent::recomputeAngle() {
  double length = range_.size();
  if (length <= SMALLEST_REAL_LENGTH)
    length = length_;

  double zeroAngle = description_.zero_point() * 2.0 * PI;

  timeRatio_ = (time_ - range_.begin_) / length;
  double timeAngle = zeroAngle + timeRatio_ * 2.0 * PI;
  if (fabs(timeAngle - timeAngle_) >= REDRAW_ANGLE ||
      fabs(zeroAngle - zeroAngle_) >= REDRAW_ANGLE) {
    zeroAngle_ = zeroAngle;
    timeAngle_ = timeAngle;
    thread::callAsync(this, &DialComponent::repaint);
  }
}

void DialComponent::paint(Graphics& g) {
  ScopedLock l(lock_);
  Painter p(description_.widget(), &g);
  juce::Rectangle<int> bounds = gui::centerSquare(p.getBounds(this));

  if (p.colors().color_size() > 2) {
    g.setColour(p.colour(Painter::FOREGROUND).
                interpolatedWith(p.colour(Painter::HIGHLIGHT), timeRatio_));
  }

  Path path;
  path.addPieSegment(bounds.getX(), bounds.getY(),
                     bounds.getWidth(), bounds.getHeight(),
                     zeroAngle_, timeAngle_, 0);

  g.fillPath(path);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
