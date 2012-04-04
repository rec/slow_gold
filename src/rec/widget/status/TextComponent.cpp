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

// Skin

TextComponent::TextComponent(const Text& desc)
    : gui::SimpleLabel(str(desc.widget().name())),
      description_(desc),
      length_(0) {
  setJustificationType(Justification::centred);
  setFont(Font(juce::Font::getDefaultMonospacedFontName(), 20, Font::plain));
  setTooltip(translate("Time Display: Shows the current playback time in minutes, "
                       "seconds and omillseconds."));
}

Samples<44100> TextComponent::getTime() const {
  Lock l(lock_);
  return time_;
}

void TextComponent::setTime(Samples<44100> time) {
  Lock l(lock_);
  time_ = time;
  String timeDisplay = formatTime(time_, length_, description_.separator().flash());
  if (timeDisplay != timeDisplay_) {
    timeDisplay_ = timeDisplay;
    thread::callAsync(this, &TextComponent::redisplay);
  }
}

void TextComponent::redisplay() {
  Lock l(lock_);
  setText(timeDisplay_, false);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
