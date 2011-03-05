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

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
