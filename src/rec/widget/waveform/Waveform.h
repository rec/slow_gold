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

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Broadcaster<const TimeAndMouseEvent&>,
                 public Listener<const juce::AudioThumbnail&>,
                 public DataListener<gui::LoopPointList>,
                 public Component {
 public:
  Waveform(const WaveformProto& desc = WaveformProto::default_instance(),
           const CursorProto* cursor = &defaultTimeCursor());

  static const CursorProto& defaultTimeCursor();

  virtual ~Waveform();
  void setAudioThumbnail(juce::AudioThumbnail* thumbnail);
  virtual void resized();

  void setTimeRange(const TimeRange&);
  const TimeRange getTimeRange() const;
	void addAllCursors(const gui::LoopPointList& loopPoints);

  virtual void operator()(const juce::AudioThumbnail&);
  virtual void operator()(const gui::LoopPointList&);

  virtual void paint(Graphics& g);
  virtual void repaint() { Component::repaint(); }

  void mouseDoubleClick(const juce::MouseEvent& e) { doClick(e, 2); }
  void mouseUp(const juce::MouseEvent& e) { doClick(e, 1); }

  Cursor* timeCursor() { return timeCursor_; }
  void layoutCursors();

  Broadcaster<const SelectionRange&>* selectionBroadcaster() {
    return &selectionBroadcaster_;
  }

 private:
  void doClick(const juce::MouseEvent& e, int clickCount);

  int timeToX(double t) const { return static_cast<int>(getWidth() * (t - range_.begin_) / range_.size()); }
  double xToTime(int x) const { return range_.begin_ + (x * range_.size()) / getWidth(); }

  void setCursorBounds(Cursor *cursor) const;

  WaveformProto desc_;
  juce::AudioThumbnail* thumbnail_;
  TimeRange range_;
  Cursor* timeCursor_;
  SelectionRange selection_;

  Broadcaster<const SelectionRange&> selectionBroadcaster_;

  DISALLOW_COPY_AND_ASSIGN(Waveform);

  friend class Cursor;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
