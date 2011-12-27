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

class OutlinedCursorLabel;

class Cursor : public Component,
               public SettableTooltipClient,
               public Listener< Samples<44100> >,
               public juce::Label::Listener {
 public:
  Cursor(const CursorProto& d, Waveform* waveform, Samples<44100> time,
         int index, bool isTimeCursor);
  virtual ~Cursor();

  virtual void operator()(const WaveformProto&);
  virtual void operator()(Samples<44100> t);

  virtual void labelTextChanged(juce::Label*);

  void setText(const String&);
  void setSelected(bool);

  void paint(Graphics& g);
  Samples<44100> getTime() const;
  bool setDragTime(Samples<44100> time);
  void setTime(Samples<44100> time);
  virtual void setTooltip(const String&);

  bool isTimeCursor() const { return (this == waveform_->timeCursor()); }

  const CursorProto& desc() const { return desc_; }

  int index() { return index_; }
  void setIndex(int index) { index_ = index; }
  void layout();
  void setCaption(const String&);
  Waveform* waveform() const { return waveform_; }
  void resizeCaption();
  void selectButtonPressed(bool);
  Component* getCaption();

 private:
  void adjustCaption();

  Waveform* const waveform_;
  CriticalSection lock_;
  CursorProto desc_;
  Samples<44100> time_;
  int index_;
  juce::Rectangle<int> bounds_;
  int dragX_;
  int mouseDragX_;
  ptr<OutlinedCursorLabel> caption_;
  int captionWidth_;
  bool showSelection_;
  WaveformProto waveDesc_;

  ptr<GlobalDataListener<WaveformProto> > waveformListener_;

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
