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
const double SMALLEST_REAL_LENGTH = 0.1;
const RealTime SMALLEST_TIME_CHANGE = 0.1;

DialComponent::DialComponent(const Dial& desc)
    : Component(str(desc.widget().name())),
      description_(desc),
      time_(0.0),
      length_(0.0),
      zeroAngle_(0.0),
      timeAngle_(0.0),
      timeRatio_(0.0) {
}

void DialComponent::operator()(RealTime time) {
  {
    ScopedLock l(lock_);
    if (false && near<int64>(time, time_, SMALLEST_TIME_CHANGE))
      return;

    time_ = time;
    Range<RealTime> range;

    for (int i = 1; i <= loops_.loop_point_size(); ++i) {
      bool isLast = (i == loops_.loop_point_size());
      if (isLast || time < loops_.loop_point(i).time()) {
        if (loops_.loop_point(i - 1).selected()) {
          range.begin_ = loops_.loop_point(i - 1).time();
          range.end_ = isLast ? length_ : RealTime(loops_.loop_point(i).time());
          break;
        } else {
          LOG(ERROR) << "Couldn't find time " << time
                     << " in " << loops_.ShortDebugString();
          return;
        }
      }
    }

    if (range.size() < 1.0)
      range.end_ = range.begin_ + 1.0;

    double length = range.size();
    double zeroAngle = description_.zero_point() * 2.0 * PI;

    timeRatio_ = (time_ - range.begin_) / length;
    double timeAngle = zeroAngle + timeRatio_ * 2.0 * PI;
    if (fabs(timeAngle - timeAngle_) < REDRAW_ANGLE &&
        fabs(zeroAngle - zeroAngle_) < REDRAW_ANGLE) {
      return;
    }
    zeroAngle_ = zeroAngle;
    timeAngle_ = timeAngle;
  }

  if (false) {
    MessageManagerLock l;
    repaint();
  } else {
    thread::callAsync(this, &DialComponent::repaint);
  }
}

void DialComponent::onDataChange(const LoopPointList& lpl) {
  ScopedLock l(lock_);
  loops_ = lpl;
}

void DialComponent::paint(Graphics& g) {
  ScopedLock l(lock_);
  Painter p(description_.widget(), &g);
  juce::Rectangle<int> bounds = gui::centerSquare(p.getBounds(this));

  if (p.colors().color_size() > 2) {
    g.setColour(p.colour(FOREGROUND).
                interpolatedWith(p.colour(HIGHLIGHT),
                                 static_cast<float>(timeRatio_)));
  }

  Path path;
  path.addPieSegment(bounds.getX(), bounds.getY(),
                     bounds.getWidth(), bounds.getHeight(),
                     static_cast<float>(zeroAngle_),
                     static_cast<float>(timeAngle_), 0.0f);

  g.fillPath(path);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
