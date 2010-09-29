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

}  // namespace time
}  // namespace gui
}  // namespace rec
