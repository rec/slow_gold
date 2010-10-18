#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/base.h"
#include "rec/widget/Time.pb.h"
#include "rec/widget/Painter.h"
#include "rec/gui/Color.pb.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace time {

class TextComponent : public juce::Component {
 public:
  explicit TextComponent(const Text& desc);

  void setTimeSamples(int samples);
  void setTimeSeconds(float time);

  virtual void paint(juce::Graphics& g);

 private:
  Text description_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TextComponent);
};

class DialComponent : public juce::Component {
 public:
  explicit DialComponent(const Dial& desc);

  // Value between 0 and 1.
  void setTimeRatio(float time) {
    time_ = time;
    repaint();
  }

  virtual void paint(juce::Graphics& g);

 private:
  Dial description_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
