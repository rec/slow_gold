#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/base.h"
#include "rec/base/scoped_ptr.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {
namespace color {
class Colors;
} // namespace color

namespace time {

class Text;

class TextComponent : public Component {
 public:
  static const float SAMPLES_PER_SECOND = 44100.0;
  TextComponent(const String& name, const Text& desc, const color::Colors& colors);

  void setTimeSamples(int samples);
  void setTimeSeconds(float time);

  void paint(Graphics& g);

 private:
  scoped_ptr<Text> desc_;
  scoped_ptr<color::Colors> colors_;
  float time_;
  Font font_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TextComponent);
};

}  // namespace time
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TIME__
