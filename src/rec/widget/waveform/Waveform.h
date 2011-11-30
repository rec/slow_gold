#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include <set>

#include "rec/base/Samples.h"
#include "rec/util/LoopPoint.h"
#include "rec/gui/component/Focusable.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Range.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/Listener.h"
#include "rec/util/DataListener.h"
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
                 public DataListener<Mode>,
                 public GlobalDataListener<WaveformProto>,
                 public DataListener<ZoomProto>,
                 public Broadcaster<const MouseWheelEvent&>,
                 public Broadcaster<const TimeAndMouseEvent&> {
 public:
  Waveform(MenuBarModel* model = NULL,
           const CursorProto* cursor = &defaultTimeCursor());
  virtual ~Waveform();

  static const CursorProto& defaultTimeCursor();

  void setAudioThumbnail(juce::AudioThumbnail* t) { thumbnail_ = t; }
  virtual void resized();

  virtual void paint(Graphics&);
  virtual void repaint() { Component::repaint(); }

  virtual void onDataChange(const LoopPointList&);
  virtual void onDataChange(const Mode&);
  virtual void onDataChange(const WaveformProto&);
  virtual void onDataChange(const ZoomProto&);

  Cursor* timeCursor() { return timeCursor_.get(); }
  void layoutCursors();

  Range<Samples<44100> > getTimeRange() const;
  Samples<44100> xToTime(int x) const;
  double pixelsPerSample() const;

  virtual void mouseWheelMove(const MouseEvent& e, float incX, float incY);
  CriticalSection* lock() { return &lock_; }

 private:
  void drawWaveform(Painter& g, const Range<Samples<44100> >&);
  void drawGrid(Graphics& g, const Range<Samples<44100> >&);

  Samples<44100> zoomEnd() const;

  void adjustCursors(const LoopPointList&);

  Cursor* newCursor(const CursorProto& d, Samples<44100> time, int index);
  void doClick(const juce::MouseEvent& e, int clickCount);
  int timeToX(Samples<44100> t) const;
  void cursorDragged(int index, int x);

  CriticalSection lock_;
  WaveformProto desc_;
  Samples<44100> length_;
  juce::AudioThumbnail* thumbnail_;
  block::BlockSet selection_;

  typedef vector<Cursor*> CursorList;
  CursorList cursors_;
  ptr<Cursor> timeCursor_;


  ZoomProto zoom_;
  bool empty_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Waveform);

  friend class Cursor;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
