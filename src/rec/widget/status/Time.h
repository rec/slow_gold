#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/widget/status/Time.pb.h"
#include "rec/util/listener/Time.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

const String formatTime(float time, bool flash=false);

class TextComponent : public juce::Label, public listener::Time {
 public:
  explicit TextComponent(const Text& desc);
  virtual void operator()(float time) { setTime(time); }
  void setTime(float time);

 private:
  Text description_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TextComponent);
};

class DialComponent : public juce::Component, public listener::Time {
 public:
  explicit DialComponent(const Dial& desc,
                         float length = 0.0f, float time = 0.0f);
  void setLength(float length);
  void setTime(float time);

  virtual void paint(juce::Graphics& g);

 private:
  CriticalSection lock_;
  Dial description_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
