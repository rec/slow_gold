#include "rec/widget/status/TextComponent.h"
#include "rec/util/FormatTime.h"
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

double TextComponent::getTime() const {
  ScopedLock l(lock_);
  return time_;
}

void TextComponent::setTime(double time) {
  ScopedLock l(lock_);
  time_ = time;

  String timeDisplay = formatTime(time_, description_.separator().flash());
  if (timeDisplay != timeDisplay_) {
    timeDisplay_ = timeDisplay;
    thread::callAsync(this, &TextComponent::redisplay);
  }
}

void TextComponent::redisplay() {
  ScopedLock l(lock_);
  setText(timeDisplay_, false);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
