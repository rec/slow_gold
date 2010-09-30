#include <math.h>

#include "rec/gui/Time.h"

#include "rec/gui/Time.pb.h"
#include "rec/gui/Color.h"
#include "rec/gui/Font.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {
namespace time {

TextComponent::TextComponent(const String& name,
                             const Text& desc,
                             const color::Colors& colors)
    : Component(name),
      desc_(new Text(desc)),
      colors_(new color::Colors(colors)),
      time_(0),
      font_(getFont(desc.font())) {
  if (!desc_->font().has_name())
    font_.setTypefaceName(Font::getDefaultMonospacedFontName());
}

void TextComponent::setTimeSamples(int samples) {
  setTimeSeconds(samples / SAMPLES_PER_SECOND);
}

void TextComponent::setTimeSeconds(float time) {
  time_ = time;
  repaint();
}

void TextComponent::paint(Graphics& g) {
  int seconds = time_;
  float fraction = time_ - seconds;
  int milliseconds = 1000 * fraction;
  // int frames = 75 * fraction;

  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  color::prepare(*colors_, &g);
  g.setFont(font_);
  char buffer[64];
  char ch = ':';
  if (desc_->separator().flash() && (seconds & 1))
    ch = ' ';
  snprintf(buffer, 64, "%02d:%02d%c%02d.%03d",
          hours, minutes, ch, seconds, milliseconds);
  g.drawSingleLineText(buffer, desc_->margin(),
                       font_.getAscent() + desc_->margin());
}


DialComponent::DialComponent(const String& name, const Dial& desc,
                             const color::Colors& colors)
    : Component(name),
      desc_(new Dial(desc)),
      colors_(new color::Colors(colors)) {
}


// Half a degree.
static const float ALMOST_ZERO = 0.5 / 360.0;

static const float PI = 3.1415926536;


void DialComponent::paint(Graphics& g) {
  color::prepare(*colors_, &g);

  float zeroAngle = desc_->zero_point() * 2.0 * PI;
  float timeAngle = zeroAngle + time_ * 2.0 * PI;
  Rectangle<int> bounds = getLocalBounds().reduced(desc_->margin(), desc_->margin());
#if 0
  Point center = bounds.getCentre();
  Point r(bounds.getWidth() / 2, bounds.getHeight() / 2);
  Point zero = center.getPointOnCircumference(r.getX(), r.getY(), zeroAngle);
  Point time = center.getPointOnCircumference(r.getX(), r.getY(), timeAngle);

  if (time_ <= ALMOST_ZERO || 1.0 - time_ <= ALMOST_ZERO) {
    int margin = desc_.margin();
    if (!desc_.empty_on_zero() && margin)
      g.drawLine(zero.getX(), zero.getY(), time.getX(), time.getY(), margin);

    return;
  }
#endif
  Path path;
  path.addPieSegment(bounds.getX(), bounds.getY(),
                     bounds.getWidth(), bounds.getHeight(),
                     zeroAngle, timeAngle, 0);

  g.fillPath(path);
}

}  // namespace time
}  // namespace gui
}  // namespace rec
