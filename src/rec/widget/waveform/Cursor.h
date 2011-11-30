#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include <set>

#include "rec/audio/Audio.h"
#include "rec/gui/Geometry.h"
#include "rec/util/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor : public Component, public Listener< Samples<44100> > {
 public:
  Cursor(const CursorProto& d, Waveform* waveform, Samples<44100> time, int index);
  virtual ~Cursor() {}

  void setTime(Samples<44100> time);
  void paint(Graphics& g);
  Samples<44100> getTime() const;

  bool isTimeCursor() const { return this == waveform_->timeCursor(); }

  const CursorProto& desc() const { return desc_; }
  void setCursorBounds(Samples<44100> time);

  virtual void operator()(Samples<44100> t);

  void setListeningToClock(bool b) { listeningToClock_ = b; }
  int index() { return index_; }
  void layout();

 private:
  Waveform* const waveform_;
  CriticalSection lock_;
  CursorProto desc_;
  Samples<44100> time_;
  const int index_;
  juce::Rectangle<int> bounds_;
  int dragX_;
  int mouseDragX_;
  bool listeningToClock_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Cursor);
};

struct CompareCursors {
  bool operator()(Cursor* x, Cursor* y) { return x->getTime() < y->getTime(); }
};

typedef std::set<Cursor*, CompareCursors> CursorSet;

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_CURSOR__
