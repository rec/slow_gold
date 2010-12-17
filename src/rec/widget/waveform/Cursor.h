#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include "rec/gui/Geometry.h"
#include "rec/util/listener/Time.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor : public Component, public listener::Time, public AsyncUpdater {
 public:
  Cursor(const CursorProto& d, Waveform* waveform, float time = 0.0f);

  virtual void operator()(float t) { setTime(t); }

  void setTime(float time);
  void paint(Graphics& g);
  float getTime() const;

  const CursorProto& desc() const { return desc_; }

  void setBoundsAsync(const juce::Rectangle<int>& bounds);
  void handleAsyncUpdate();

 private:
  Waveform* const waveform_;
  CriticalSection lock_;
  const CursorProto desc_;
  float time_;
  juce::Rectangle<int> bounds_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Cursor);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_CURSOR__
