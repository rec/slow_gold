#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/util/Range.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class CursorProto;

struct TimeAndMouseEvent {
  float time_;
  const juce::MouseEvent* mouseEvent_;
  int clickCount_;
};

typedef std::pair<float, float> TimeBounds;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public listener::Broadcaster<const TimeAndMouseEvent&>,
                 public listener::Listener<const juce::AudioThumbnail&>,
                 public Component {
 public:
  Waveform(const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &CursorProto::default_instance());
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
  void mouseDoubleClick(const juce::MouseEvent& e) { doClick(e, 2); }
  void mouseUp(const juce::MouseEvent& e) { doClick(e, 1); }
  virtual void repaint() { Component::repaint(); }

  Cursor* timeCursor() { return timeCursor_; }

 private:
  void doClick(const juce::MouseEvent& e, int clickCount);
  void layoutCursors();

  CriticalSection lock_;
  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  Range<float> range_;
  Cursor* timeCursor_;

  DISALLOW_COPY_AND_ASSIGN(Waveform);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
