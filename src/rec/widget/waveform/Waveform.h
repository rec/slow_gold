#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include <set>

#include "rec/base/RealTime.h"
#include "rec/util/LoopPoint.h"
#include "rec/gui/component/Focusable.h"
#include "rec/util/Mode.pb.h"
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
struct MouseWheelEvent;
struct TimeAndMouseEvent;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public gui::component::Focusable<Component>,
                 public DataListener<LoopPointList>,
                 public DataListener<ZoomProto>,
                 public DataListener<Mode>,
                 public Broadcaster<const MouseWheelEvent&>,
                 public Broadcaster<const TimeAndMouseEvent&>
                 /*public Broadcaster<const TimeSelection&>*/ {
 public:
  Waveform(const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &defaultTimeCursor());
  virtual ~Waveform();

  static const CursorProto& defaultTimeCursor();

  void setAudioThumbnail(juce::AudioThumbnail* t) { thumbnail_ = t; }
  virtual void resized();
  void setEmpty(bool empty);

  virtual void paint(Graphics&);
  virtual void repaint() { Component::repaint(); }
  virtual void onDataChange(const LoopPointList&);
  virtual void onDataChange(const ZoomProto&);
  virtual void onDataChange(const Mode&);

  Cursor* timeCursor() { return timeCursor_; }
  void layoutCursors();

  Range<RealTime> getTimeRange() const;
  double xToTime(int x) const;
  double pixelsPerSecond() const;

  virtual void mouseWheelMove(const MouseEvent& e, float incX, float incY);
  CriticalSection* lock() { return &lock_; }

 private:
  void drawGrid(Graphics& g, const Range<RealTime>&);
  void adjustCursors(const LoopPointList&);

  Cursor* newCursor(const CursorProto& d, double time, int index);
  void doClick(const juce::MouseEvent& e, int clickCount);
  int timeToX(RealTime t) const;
  void cursorDragged(int index, int x);

  CriticalSection lock_;
  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  Cursor* timeCursor_;
  block::BlockSet selection_;

  ZoomProto zoom_;
  bool empty_;

  DISALLOW_COPY_AND_ASSIGN(Waveform);

  friend class Cursor;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
