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

static const double PI = 3.1415926536;

DialComponent::DialComponent(const Dial& desc, double length, double time)
    : Component(desc.widget().name().c_str()),
      description_(desc),
      length_(length),
      time_(time),
      range_(0.0, 0.0) {
}

void DialComponent::paint(Graphics& g) {
#if 0
  static int painted = 0;
  if (!(++painted % 10))
    std::cout << std::endl;
  std::cout << ".";
#endif

  ScopedLock l(lock_);
  double length = range_.size();
  if (length <= 0.01)
    length = length_;

  double timeRatio = (time_ - range_.begin_) / length;

  Painter p(description_.widget(), &g);
  juce::Rectangle<int> bounds = gui::centerSquare(p.getBounds(this));
  double zeroAngle = description_.zero_point() * 2.0 * PI;
  double timeAngle = zeroAngle + timeRatio * 2.0 * PI;

  if (p.colors().color_size() > 2) {
    g.setColour(p.colour(Painter::FOREGROUND).
                interpolatedWith(p.colour(Painter::HIGHLIGHT), timeRatio));
  }

  if (false)
    return;

  Path path;
#if 0
  LOG(ERROR)
    << "bounds.getX(): " << bounds.getX()
    << ", bounds.getY()," << bounds.getY()
    << ", bounds.getWidth(): " << bounds.getWidth()
    << ", bounds.getHeight()," << bounds.getHeight()
    << ", zeroAngle: " << zeroAngle
    << ", timeAngle: " << timeAngle
    << ", length_: " << length_
    << ", length: " << length
    << ", timeRatio: " << timeRatio
    << ", range.begin_: " << range_.begin_
    << ", range.end_: " << range_.end_;
    ;
#endif
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

void DialComponent::operator()(const SelectionRange& c) {
  ScopedLock l(lock_);
  range_ = TimeRange(c);
  thread::callAsync(this, &DialComponent::repaint);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
