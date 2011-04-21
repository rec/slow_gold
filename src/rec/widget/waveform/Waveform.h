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
#include "rec/widget/waveform/CursorTime.h"
#include "rec/widget/waveform/TimeAndMouseEvent.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {

namespace slow {
class Instance;
}

namespace widget {
namespace waveform {

class Cursor;
class CursorProto;
struct CursorTime;
struct TimeAndMouseEvent;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component,
                 public Broadcaster<const CursorTime&>, 
                 public Broadcaster<const SelectionRange&> {
 public:
  Waveform(slow::Instance* instance,
           const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &defaultTimeCursor());
  virtual ~Waveform();

  static const CursorProto& defaultTimeCursor();

  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized();

	void addAllCursors(const gui::LoopPointList& loopPoints);

  virtual void paint(Graphics& g);
  virtual void repaint() { Component::repaint(); }

  void mouseDoubleClick(const juce::MouseEvent& e) { doClick(e, 2); }
  void mouseUp(const juce::MouseEvent& e) { doClick(e, 1); }

  Cursor* timeCursor() { return timeCursor_; }
  void layoutCursors();

  TimeRange getTimeRange() const;

 private:
  void doClick(const juce::MouseEvent& e, int clickCount);
  void setSelection(const gui::LoopPointList&);

  int timeToX(double t) const;
  double xToTime(int x) const;

  void cursorDragged(int index, int x);

  Instance* instance_;
  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  Cursor* timeCursor_;
  SelectionRange selection_;

  ZoomProto zoom_;

  DISALLOW_COPY_AND_ASSIGN(Waveform);

  friend class Cursor;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
