#include <math.h>

#include "rec/widget/status/DialComponent.h"
#include "rec/util/StateListener.h"
#include "rec/gui/Color.h"
#include "rec/gui/Geometry.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Math.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/Painter.h"

using rec::gui::Colors;
using rec::gui::Color;

using namespace juce;

namespace rec {
namespace widget {
namespace status {
namespace time {

// Skin

// Half a degree.
//static const double ALMOST_ZERO = 0.5 / 360.0;

const double DialComponent::PI = 3.14159265358979323846264;
const double DialComponent::REDRAW_ANGLE = 2.0 * DialComponent::PI * 0.001;
const SampleTime SMALLEST_TIME_CHANGE = 44;

DialComponent::DialComponent(const Dial& desc)
        : Component(str(desc.widget().name())),
            StateListener<SampleTime>(desc.use_global_clock()),
            description_(desc),
            time_(0),
            zeroAngle_(0.0),
            timeAngle_(0.0),
            timeRatio_(0.0),
            empty_(true) {
    description_.mutable_widget()->set_transparent(true);
    setTooltip("Time Dial: Shows graphically how much of the loop remains.");
}

static const bool USE_CONTIGUOUS_SEGMENTS = true;

static bool SMALLEST_CHANGE_ENABLED = false;

bool DialComponent::doSetTime(SampleTime time) {
    Lock l(lock_);
    if (SMALLEST_CHANGE_ENABLED && near<int64>(time, time_, SMALLEST_TIME_CHANGE))
        return false;

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
        LOG(ERROR) << "Setting the time too small!";
        timeAngle_ = zeroAngle_ = 0.0;
        timeRatio_ = 1.0;
        return false;
    }

    double length = static_cast<double>(range.size());
    double zeroAngle = description_.zero_point() * 2.0 * PI;

    timeRatio_ = std::min(1.0, (time_ - range.begin_) / length);
    if (timeRatio_ < 0.0) {
        LOG(DFATAL) << "Negative time ratio " << timeRatio_;
        timeRatio_ = 0.0;
    }
    double timeAngle = zeroAngle + timeRatio_ * 2.0 * PI;
    if (fabs(timeAngle - timeAngle_) < REDRAW_ANGLE &&
            fabs(zeroAngle - zeroAngle_) < REDRAW_ANGLE) {
        return false;
    }
    zeroAngle_ = zeroAngle;
    timeAngle_ = timeAngle;

    return true;
}

void DialComponent::setTime(SampleTime time) {
    if (doSetTime(time)) {
        MessageManagerLock l(thread());
        if (l.lockWasGained())
            repaint();
    }
}

void DialComponent::operator()(const waveform::Viewport& vp) {
    Lock l(lock_);

    empty_ = not vp.loop_points().length();
    loops_ = vp.loop_points();
    setTime(time_);
    repaint();
}

void DialComponent::paint(Graphics& g) {
    Lock l(lock_);

    Painter p(description_.widget(), &g);
    if (empty_)
        return;
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
