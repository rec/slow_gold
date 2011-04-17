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
};

struct CursorTime {
  int cursor_;
  double time_;
};

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component {
 public:
  Waveform(Instance* instance,
           const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &defaultTimeCursor());

  static const CursorProto& defaultTimeCursor();

  virtual ~Waveform();
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
