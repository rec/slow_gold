#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/util/listener/Listener.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

const String formatTime(float time, bool flash=false);

class TextComponent : public juce::Label, public listener::Listener<float> {
 public:
  explicit TextComponent(const Text& desc);
  virtual void operator()(float time) { setTime(time); }
  void setTime(float time);
  void redisplay();

 private:
  Text description_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TextComponent);
};

// TODO: must get updates for length!
class DialComponent : public Component, public listener::Listener<float> {
 public:
  explicit DialComponent(const Dial& desc, float length = 0.0f, float time = 0.0f);
  void setLength(float length);
  void setTime(float time);

  virtual void operator()(float time) { setTime(time); }
  virtual void paint(juce::Graphics& g);
  virtual void repaint() { Component::repaint(); }

 private:
  CriticalSection lock_;
  Dial description_;
  float length_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
