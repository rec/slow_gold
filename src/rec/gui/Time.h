#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/basictypes.h"
#include "rec/gui/Time.pb.h"
#include "rec/gui/Color.h"
#include "rec/gui/Font.h"

namespace rec {
namespace gui {
namespace time {

class TextComponent : public Component {
 public:
  static const float SAMPLES_PER_SECOND = 44100.0;
  TextComponent(const String& name, const Text& desc, const color::Colors& colors)
      : Component(name),
        desc_(desc),
        colors_(colors),
        time_(0),
        font_(getFont(desc.font())) {
    if (!desc_.font().has_name())
      font_.setTypefaceName(Font::getDefaultMonospacedFontName());
  }

  void setTimeSamples(int samples) { setTimeSeconds(samples / SAMPLES_PER_SECOND); }
  void setTimeSeconds(float time) {
    time_ = time;
    repaint();
  }

  void paint(Graphics& g) {
    int seconds = time_;
    float fraction = time_ - seconds;
    int milliseconds = 1000 * fraction;
    // int frames = 75 * fraction;

    int minutes = seconds / 60;
    int hours = minutes / 60;
    seconds %= 60;

    color::prepare(colors_, &g);
    g.setFont(font_);
    char buffer[64];
    char ch = ':';
    if (desc_.separator().flash() && (seconds & 1))
      ch = ' ';
    snprintf(buffer, 64, "%02d:%02d%c%02d.%03d",
            hours, minutes, ch, seconds, milliseconds);
    g.drawSingleLineText(buffer, desc_.margin(),
                         font_.getAscent() + desc_.margin());
  }

 private:
  Text desc_;
  color::Colors colors_;
  float time_;
  Font font_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TextComponent);
};

}  // namespace time
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TIME__
