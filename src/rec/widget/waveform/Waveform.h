#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include <set>

#include "rec/gui/LoopPoint.pb.h"
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

struct TimeAndMouseEvent {
  double time_;
  const juce::MouseEvent* mouseEvent_;
  int clickCount_;
  juce::ModifierKeys modifierKeys_;
};

struct CursorTime {
  int cursor_;
  double time_;
};

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Broadcaster<const TimeAndMouseEvent&>,
                 public Listener<const juce::AudioThumbnail&>,
                 public Listener<const ZoomProto&>,
                 public DataListener<gui::LoopPointList>,
                 public Component {
 public:
  Waveform(const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &defaultTimeCursor());

  static const CursorProto& defaultTimeCursor();

  virtual ~Waveform();
  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized();

	void addAllCursors(const gui::LoopPointList& loopPoints);

  virtual void operator()(const juce::AudioThumbnail&);
  virtual void operator()(const gui::LoopPointList&);
  virtual void operator()(const ZoomProto&);

  virtual void paint(Graphics& g);
  virtual void repaint() { Component::repaint(); }

  void mouseDoubleClick(const juce::MouseEvent& e) { doClick(e, 2); }
  void mouseUp(const juce::MouseEvent& e) { doClick(e, 1); }

  Cursor* timeCursor() { return timeCursor_; }
  void layoutCursors();

  Broadcaster<const SelectionRange&>* selectionBroadcaster() {
    return &selectionBroadcaster_;
  }

  Broadcaster<const CursorTime&>* cursorTimeBroadcaster() {
    return &cursorTimeBroadcaster_;
  }

  DataListener<ZoomProto>* zoomData() { return &zoomData_; }
  TimeRange getTimeRange() const;

 private:
  void doClick(const juce::MouseEvent& e, int clickCount);
  void setSelection(const gui::LoopPointList&);

  int timeToX(double t) const;
  double xToTime(int x) const;

  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  Cursor* timeCursor_;
  SelectionRange selection_;

  Broadcaster<const SelectionRange&> selectionBroadcaster_;
  Broadcaster<const CursorTime&> cursorTimeBroadcaster_;

  class ZoomData : public DataListener<ZoomProto> {
   public:
    ZoomData(Waveform* waveform) : waveform_(waveform) {}
    virtual void operator()(const ZoomProto& zoom) { (*waveform_)(zoom); }

   private:
    Waveform* const waveform_;

    DISALLOW_COPY_ASSIGN_AND_EMPTY(ZoomData);
  };

  ZoomData zoomData_;
  ZoomProto zoom_;

  DISALLOW_COPY_AND_ASSIGN(Waveform);

  friend class Cursor;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
