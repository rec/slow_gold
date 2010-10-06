#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/base.h"
#include "rec/widget/Time.pb.h"
#include "rec/gui/Color.pb.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace time {

class TextComponent : public Component {
 public:
  static const float SAMPLES_PER_SECOND = 44100.0;
  TextComponent(const String& name, const Text& desc, const gui::Colors& colors);

  void setTimeSamples(int samples);
  void setTimeSeconds(float time);

  void paint(Graphics& g);

 private:
  scoped_ptr<Text> desc_;
  scoped_ptr<gui::Colors> colors_;
  float time_;
  Font font_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TextComponent);
};

class DialComponent : public Component {
 public:
  DialComponent(const String& name, const Dial& desc, const gui::Colors& colors);

  // Value between 0 and 1.
  void setTimeRatio(float time) {
    time_ = time;
    repaint();
  }

  void paint(Graphics& g);

 private:
  scoped_ptr<Dial> desc_;
  scoped_ptr<gui::Colors> colors_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
