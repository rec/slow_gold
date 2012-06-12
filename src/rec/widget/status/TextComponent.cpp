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
  setTooltip(Trans("Time Display: Shows the current playback time in minutes, "
                       "seconds and millseconds."));
}

SampleTime TextComponent::getTime() const {
  Lock l(lock_);
  return time_;
}

bool TextComponent::setTime(SampleTime t) {
  Lock l(lock_);
  time_ = t;
  bool flash = description_.separator().flash();
  String timeDisplay = formatTime(time_, length_, flash);

  bool res = (timeDisplay == timeDisplay_);
  timeDisplay_ = timeDisplay;
  return res;
}

void TextComponent::redisplay() {
  String dis;
  {
    Lock l(lock_);
    dis = timeDisplay_;
  }

  setText(dis, false);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
