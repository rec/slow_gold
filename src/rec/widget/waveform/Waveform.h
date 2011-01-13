#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include <set>

#include "rec/util/Range.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class CursorProto;

struct TimeAndMouseEvent {
  double time_;
  const juce::MouseEvent* mouseEvent_;
  int clickCount_;
};

typedef Range<double> TimeBounds;


// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public listener::Broadcaster<const TimeAndMouseEvent&>,
                 public listener::Listener<const juce::AudioThumbnail&>,
                 public Component {
 public:
  Waveform(const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &CursorProto::default_instance());
  virtual ~Waveform();
  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized();

  void layoutCursor(Cursor* cursor);
  Cursor* addCursor(const CursorProto& desc, double time);
  void moveCursor(Cursor* cursor, double time);
  void setTimeBounds(const TimeBounds&);
  const TimeBounds getTimeBounds() const;

  virtual void operator()(const juce::AudioThumbnail&);

  virtual void paint(Graphics& g);
  virtual void repaint() { Component::repaint(); }

  void mouseDoubleClick(const juce::MouseEvent& e) { doClick(e, 2); }
  void mouseUp(const juce::MouseEvent& e) { doClick(e, 1); }

  Cursor* timeCursor() { return timeCursor_; }

 private:
  void doClick(const juce::MouseEvent& e, int clickCount);

  CriticalSection lock_;
  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  TimeBounds range_;
  Cursor* timeCursor_;

  typedef std::set<TimeBounds> SelectionRange;
  SelectionRange selection_;

  DISALLOW_COPY_AND_ASSIGN(Waveform);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
