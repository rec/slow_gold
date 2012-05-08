#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/Samples.h"
#include "rec/util/Listener.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class TextComponent : public gui::SimpleLabel,
                      public Listener< Samples<44100> > {
 public:
  explicit TextComponent(const Text& desc = Text::default_instance());
  virtual void operator()(Samples<44100> time) { setTime(time); }

  Samples<44100> getTime() const;
  bool setTime(Samples<44100> time);
  void setLength(Samples<44100> len) { length_ = len; }
  void redisplay();

 private:
  Text description_;
  Samples<44100> time_;
  String timeDisplay_;
  Samples<44100> length_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TextComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
