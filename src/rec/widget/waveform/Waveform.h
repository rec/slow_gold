#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include "rec/widget/Waveform.pb.h"
#include "rec/util/listener/Broadcaster.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/widget/waveform/Cursor.h"

namespace rec {
namespace widget {
namespace waveform {

// This handles waveform display only (no command information).
class Waveform : public Component,
                 public listener::Broadcaster<float> {
 public:
  explicit Waveform(const WaveformProto& desc);
  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized() { layoutCursors(); }

  void layoutCursor(Cursor* cursor);
  Cursor* addCursor(const CursorProto& desc, float time);
  void moveCursor(Cursor* cursor, float time);
  void setTimeBounds(float begin, float end);
  virtual void paint(Graphics& g);
  void mouseUp(const MouseEvent& e);

 private:
  void layoutCursors();

  CriticalSection lock_;
  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  float begin_;
  float end_;
  Cursor* timeCursor_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(WaveformProto);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
