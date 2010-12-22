#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/listener/Broadcaster.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class CursorProto;

typedef std::pair<float, const juce::MouseEvent*> TimeAndMouseEvent;
typedef std::pair<float, float> TimeBounds;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component,
                 public listener::Broadcaster<const TimeAndMouseEvent&>,
                 public listener::Listener<const juce::AudioThumbnail&> {
 public:
  explicit Waveform(const WaveformProto& desc);
  virtual ~Waveform();
  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized() { layoutCursors(); }

  void layoutCursor(Cursor* cursor);
  Cursor* addCursor(const CursorProto& desc, float time);
  void moveCursor(Cursor* cursor, float time);
  void setTimeBounds(float begin, float end);
  const TimeBounds getTimeBounds() const;
  virtual void operator()(const juce::AudioThumbnail&);
  virtual void paint(Graphics& g);
  void mouseUp(const juce::MouseEvent& e);
  virtual void repaint() { Component::repaint(); }

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
