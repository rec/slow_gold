#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/base.h"
#include "rec/widget/Time.pb.h"
#include "rec/widget/Widget.h"
#include "rec/gui/Color.pb.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace time {

class TextComponent : public WidgetBase<Text>, public juce::Component {
 public:
  explicit TextComponent(const Text& desc);

  void setTimeSamples(int samples);
  void setTimeSeconds(float time);

  virtual void paint(juce::Graphics& g, const juce::Rectangle<int>& bounds);

 private:
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TextComponent);
};

class DialComponent : public WidgetBase<Dial>, public juce::Component {
 public:
  explicit DialComponent(const Dial& desc);

  // Value between 0 and 1.
  void setTimeRatio(float time) {
    time_ = time;
    repaint();
  }

  void paint(juce::Graphics& g, const juce::Rectangle<int>& bounds);

 private:
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
