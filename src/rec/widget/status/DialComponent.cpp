#include <math.h>

#include "rec/widget/status/DialComponent.h"
#include "rec/util/Math.h"
#include "rec/gui/Color.h"
#include "rec/gui/Geometry.h"
#include "rec/widget/Painter.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/thread/CallAsync.h"

using rec::gui::Colors;
using rec::gui::Color;

using namespace juce;

namespace rec {
namespace widget {
namespace status {
namespace time {

// Skin

// Half a degree.
static const double ALMOST_ZERO = 0.5 / 360.0;

const double DialComponent::PI = 3.14159265358979323846264;
const double DialComponent::REDRAW_ANGLE = 2.0 * DialComponent::PI * 0.001;
const double SMALLEST_REAL_LENGTH = 0.1;
const SampleTime SMALLEST_TIME_CHANGE = 44;

DialComponent::DialComponent(const Dial& desc)
    : Component(str(desc.widget().name())),
      description_(desc),
      time_(0),
      zeroAngle_(0.0),
      timeAngle_(0.0),
      timeRatio_(0.0) {
  description_.mutable_widget()->set_transparent(true);
  setTooltip("Time Dial: Shows graphically how much of the loop remains.");
}

static const bool USE_CONTIGUOUS_SEGMENTS = true;

void DialComponent::operator()(SampleTime time) {
  if (setTime(time))
    repaint();
}

bool DialComponent::setTime(SampleTime time) {
  {
    Lock l(lock_);
    if (false && near<int64>(time, time_, SMALLEST_TIME_CHANGE))
      return false;  // TODO: why is this disabled.

    if (!loops_.has_length())
      return false;

    time_ = time;
    Range<SampleTime > range;

    if (USE_CONTIGUOUS_SEGMENTS)
      range = audio::contiguousSelectionContaining(loops_, time);

    if (range.size() < SMALLEST_TIME_CHANGE) {
      int seg = audio::getSegment(loops_, time);
      bool atEnd = (seg == loops_.loop_point_size() - 1);
      range.begin_ = loops_.loop_point(seg).time();
      range.end_ = atEnd ? loops_.length() : loops_.loop_point(seg + 1).time();
    }

    if (range.size() < SMALLEST_TIME_CHANGE) {
      timeAngle_ = zeroAngle_ = 0.0;
      timeRatio_ = 1.0;
      return false;
    }

    double length = static_cast<double>(range.size());
    double zeroAngle = description_.zero_point() * 2.0 * PI;

    timeRatio_ = std::max(0.0, std::min(1.0, (time_ - range.begin_) / length));
    double timeAngle = zeroAngle + timeRatio_ * 2.0 * PI;
    if (fabs(timeAngle - timeAngle_) < REDRAW_ANGLE &&
        fabs(zeroAngle - zeroAngle_) < REDRAW_ANGLE) {
      return false;
    }
    zeroAngle_ = zeroAngle;
    timeAngle_ = timeAngle;
  }

  return true;
}

void DialComponent::operator()(const waveform::Viewport& vp) {
  Lock l(lock_);
  loops_ = vp.loop_points();
  timeAngle_ = zeroAngle_ = 0.0;
}

void DialComponent::paint(Graphics& g) {
  Lock l(lock_);

  Painter p(description_.widget(), &g);
  juce::Rectangle<int> bounds = gui::centerSquare(p.getBounds(this));

  Path path;

  if (p.colors().color_size() > 2) {
    g.setColour(p.colour(FOREGROUND).
                interpolatedWith(p.colour(HIGHLIGHT),
                                 static_cast<float>(timeRatio_)));
  }

  path.addPieSegment(static_cast<float>(bounds.getX()),
                     static_cast<float>(bounds.getY()),
                     static_cast<float>(bounds.getWidth()),
                     static_cast<float>(bounds.getHeight()),
                     static_cast<float>(zeroAngle_),
                     static_cast<float>(timeAngle_), 0.0f);

  g.fillPath(path);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
