#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/app/LanguageListener.h"
#include "rec/base/SampleTime.h"
#include "rec/data/DataListener.h"
#include "rec/util/HasThread.h"
#include "rec/util/Listener.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/widget/status/Time.pb.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class TextComponent : public gui::SimpleLabel,
                      public app::LanguageListener,
                      public DataListener<waveform::Viewport>,
                      public Listener<SampleTime>,
                      public HasThread {
 public:
  explicit TextComponent(const Text& desc = Text::default_instance());
  virtual void operator()(SampleTime time) { setTime(time); }

  SampleTime getTime() const;
  void setTime(SampleTime time);
  void setLength(SampleTime len) { length_ = len; }
  virtual void languageChanged();

 protected:
  virtual void operator()(const waveform::Viewport&);
  bool doSetTime(SampleTime time);
  void redisplay();

 private:
  Text description_;
  SampleTime time_;
  String timeDisplay_;
  SampleTime length_;
  SampleRate sampleRate_;
  bool empty_;

  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TextComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
