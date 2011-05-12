#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include <set>

#include "rec/gui/audio/LoopPoint.pb.h"
#include "rec/util/Range.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/listener/DataListener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class CursorProto;
struct CursorTime;
struct MouseWheelEvent;
struct TimeAndMouseEvent;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component,
                 public Listener<juce::AudioThumbnail*>,
                 public Listener<const ZoomProto&>,
                 public Broadcaster<const CursorTime&>,
                 public Broadcaster<const MouseWheelEvent&>,
                 public Broadcaster<const TimeAndMouseEvent&>,
                 public Broadcaster<const TimeSelection&> {
 public:
  Waveform(const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &defaultTimeCursor());
  virtual ~Waveform();

  static const CursorProto& defaultTimeCursor();

  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized();

	void addAllCursors(const gui::audio::LoopPointList& loopPoints);

  virtual void paint(Graphics& g);
  virtual void repaint() { Component::repaint(); }
  virtual void operator()(juce::AudioThumbnail* t) { setAudioThumbnail(t); }
  virtual void operator()(const ZoomProto& p);

  Cursor* timeCursor() { return timeCursor_; }
  void layoutCursors();

  TimeRange getTimeRange() const;
  double xToTime(int x) const;
  double pixelsPerSecond() const;

  virtual void mouseWheelMove(const MouseEvent& e, float incX, float incY);

 private:
  void drawGrid(const TimeRange&);
  void drawCaptions(const TimeRange&);

  Cursor* newCursor(const CursorProto& d, double time, int index);
  void doClick(const juce::MouseEvent& e, int clickCount);
  void setSelection(const gui::audio::LoopPointList&);

  int timeToX(double t) const;

  void cursorDragged(int index, int x);

  CriticalSection lock_;
  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  Cursor* timeCursor_;
  TimeSelection selection_;

  ZoomProto zoom_;

  DISALLOW_COPY_AND_ASSIGN(Waveform);

  friend class Cursor;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
