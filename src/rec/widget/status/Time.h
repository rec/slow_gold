#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/gui/CuttableComponent.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/ClockUpdate.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

const String formatTime(double time, bool flash = false, bool displayMs = true);

class TextComponent : public gui::SimpleLabel,
                      public Listener<const ClockUpdate&> {
 public:
  explicit TextComponent(const Text& desc = Text::default_instance());
  virtual void operator()(const ClockUpdate& c);

  double getTime() const { return time_; }
  void setTime(double time);
  void redisplay();

 private:
  Text description_;
  double time_;

  DISALLOW_COPY_AND_ASSIGN(TextComponent);
};

// TODO: must get updates for length!
class DialComponent : public gui::CuttableComponent,
                      public Listener<const ClockUpdate&> {
 public:
  explicit DialComponent(const Dial& desc, double length = 0.0f, double time = 0.0f);
  void setLength(double length);
  void setTime(double time);

  virtual void operator()(const ClockUpdate& c) { c.update(this); }
  virtual void paint(juce::Graphics& g);
  virtual void repaint() { gui::CuttableComponent::repaint(); }

 private:
  CriticalSection lock_;
  Dial description_;
  double length_;
  double time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
