#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/util/listener/Broadcaster.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class CursorProto;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component,
                 public listener::Broadcaster<float>,
                 public listener::Listener<const juce::AudioThumbnail&>,
                 public AsyncUpdater {
 public:
  explicit Waveform(const WaveformProto& desc);
  virtual ~Waveform();
  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized() { layoutCursors(); }

  virtual void handleAsyncUpdate() { repaint(); }

  void layoutCursor(Cursor* cursor);
  Cursor* addCursor(const CursorProto& desc, float time);
  void moveCursor(Cursor* cursor, float time);
  void setTimeBounds(float begin, float end);
  std::pair<float, float> getTimeBounds() const;
  virtual void operator()(const juce::AudioThumbnail&) { triggerAsyncUpdate(); }

  virtual void paint(Graphics& g);
  void mouseUp(const juce::MouseEvent& e);

 private:
  void layoutCursors();

  CriticalSection lock_;
  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  float begin_;
  float end_;
  Cursor* timeCursor_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Waveform);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
