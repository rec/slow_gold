#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include <set>

#include "rec/base/SampleTime.h"
#include "rec/data/DataListener.h"
#include "rec/util/Listener.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Range.h"
#include "rec/util/block/Block.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class CursorProto;
class WaveformPainter;
class WaveformModel;

struct MouseWheelEvent;
struct TimeAndMouseEvent;

typedef vector<Cursor*> CursorList;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component,
                 public SettableTooltipClient,
                 public DataListener<Viewport>,
                 public GlobalDataListener<Mode>,
                 public GlobalDataListener<WaveformProto>,
                 public Broadcaster<const MouseWheelEvent&>,
                 public Broadcaster<const TimeAndMouseEvent&> {
 public:
  Waveform(MenuBarModel* model = NULL);
  virtual ~Waveform();
  void init();

  static const CursorProto& defaultTimeCursor();

  void setAudioThumbnail(juce::AudioThumbnail*);
  virtual void resized();

  virtual void paint(Graphics&);
  virtual void operator()(const Mode&);
  virtual void operator()(const WaveformProto&);
  virtual void operator()(const Viewport& vp);

  Cursor* timeCursor() { return timeCursor_.get(); }

  const CursorList& getCursors() const { return cursors_; }
  CursorList* getCursorsMutable() { return &cursors_; }

  virtual void mouseWheelMove(const MouseEvent& e, const juce::MouseWheelDetails&);
  CriticalSection* lock() { return &lock_; }
  int getCursorX(uint index) const;
  void setCursorText(int index, const String& text);
  void setIsDraggingCursor(bool d);
  bool isDraggingCursor() const;
  void repaintBlock(block::Block);
  void repaintBlocks(const block::BlockSet&);

  void adjustCursors(const LoopPointList& loopPoints,
                     const block::BlockSet& dirty);
  void setSelected(int index, bool selected);
  const WaveformModel& model() { return *model_; }
  static void translateAll();
  void setLoading(bool loading);
  void setSampleRate(SampleRate);

 private:
  void layout();
  void viewportChanged();

  void doClick(const juce::MouseEvent& e, int clickCount);
  void cursorDragged(int index, int x);

  CriticalSection lock_;
  juce::AudioThumbnail* thumbnail_;
  ptr<WaveformModel> model_;
  ptr<WaveformPainter> painter_;

  CursorList cursors_;
  ptr<Cursor> timeCursor_;

  juce::MouseCursor	zoomCursor_;
  bool loading_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Waveform);

  friend class Cursor;
  friend class WaveformPainter;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
