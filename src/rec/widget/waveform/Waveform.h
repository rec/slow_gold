#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include <set>

#include "rec/base/Samples.h"
#include "rec/util/LoopPoint.h"
#include "rec/data/DataListener.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Range.h"
#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/block/Block.h"
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

typedef vector<Cursor*> CursorList;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component,
                 public SettableTooltipClient,
                 public DataListener<LoopPointList>,
                 public GlobalDataListener<Mode>,
                 public GlobalDataListener<WaveformProto>,
                 public DataListener<ZoomProto>,
                 public Broadcaster<const MouseWheelEvent&>,
                 public Broadcaster<const TimeAndMouseEvent&>
{
 public:
  Waveform(MenuBarModel* model = NULL,
           const CursorProto* cursor = &defaultTimeCursor());
  virtual ~Waveform();

  virtual void startListening();

  static const CursorProto& defaultTimeCursor();

  void setAudioThumbnail(juce::AudioThumbnail* t) { thumbnail_ = t; }
  virtual void resized() { layout(); }

  virtual void paint(Graphics&);
  virtual void operator()(const LoopPointList&);
  virtual void operator()(const Mode&);
  virtual void operator()(const WaveformProto&);
  virtual void operator()(const ZoomProto&);

  Cursor* timeCursor() { return timeCursor_.get(); }

  Range<Samples<44100> > getTimeRange() const;
  Samples<44100> xToTime(int x) const;
  double pixelsPerSample() const;

  const CursorList& getCursors() const { return cursors_; }
  CursorList* getCursorsMutable() { return &cursors_; }

  virtual void mouseWheelMove(const MouseEvent& e, float incX, float incY);
  CriticalSection* lock() { return &lock_; }
  int getCursorX(uint index) const;
  void setCursorText(int index, const String& text);
  void setIsDraggingCursor(bool d);
  bool isDraggingCursor() const { Lock l(lock_); return isDraggingCursor_; }
  void repaintBlock(block::Block);
  void repaintBlocks(const block::BlockSet&);

  void adjustCursors(LoopPointList loopPoints, block::BlockSet dirty);
  void setSelected(int index, bool selected);

 private:
  void drawWaveform(Painter& g, const Range<Samples<44100> >&);
  void drawGrid(Graphics& g, const Range<Samples<44100> >&);
  void layout();

  Samples<44100> zoomEnd() const;

  void doClick(const juce::MouseEvent& e, int clickCount);
  int timeToX(Samples<44100> t) const;
  void cursorDragged(int index, int x);

  CriticalSection lock_;
  WaveformProto desc_;
  Samples<44100> length_;
  juce::AudioThumbnail* thumbnail_;
  block::BlockSet selection_;

  CursorList cursors_;
  ptr<Cursor> timeCursor_;

  ZoomProto zoom_;
  bool empty_;
  bool isDraggingCursor_;

  juce::MouseCursor	zoomCursor_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Waveform);

  friend class Cursor;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
