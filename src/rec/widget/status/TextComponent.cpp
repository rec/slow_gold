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
      length_(0),
      sampleRate_(44100.0),
      empty_(true) {
  setJustificationType(Justification::centred);
  setFont(Font(juce::Font::getDefaultMonospacedFontName(), 20, Font::plain));
}

SampleTime TextComponent::getTime() const {
  Lock l(lock_);
  return time_;
}

void TextComponent::operator()(const waveform::Viewport& vp) {
  Lock l(lock_);
  sampleRate_ = vp.loop_points().sample_rate();
  empty_ = !vp.loop_points().has_sample_rate();
}

void TextComponent::languageChanged() {
  Lock l(lock_);
  setTooltip(Trans("Time Display: Shows the current playback time in minutes, "
                   "seconds and millseconds."));
}

bool TextComponent::setTime(SampleTime t) {
  bool res;

  Lock l(lock_);
  time_ = t;

  if (empty_) {
    res = timeDisplay_ == "";
    timeDisplay_ = "";
  } else {
    bool f = description_.separator().flash();
    TimeFormat tf(f ? TimeFormat::FLASH : TimeFormat::NO_FLASH);
    String timeDisplay = tf.format(time_, length_, sampleRate_);

    res = (timeDisplay == timeDisplay_);
    timeDisplay_ = timeDisplay;
  }
  return res;
}

void TextComponent::redisplay() {
  String dis;
  {
    Lock l(lock_);
    dis = timeDisplay_;
  }

  setText(dis, juce::dontSendNotification);
}

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
