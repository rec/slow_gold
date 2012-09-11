#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include <set>

#include "rec/app/LanguageListener.h"
#include "rec/audio/Audio.h"
#include "rec/gui/Geometry.h"
#include "rec/util/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;

Cursor* makeCursor(const CursorProto& cp, Waveform* w, int index,
                   SampleTime time);
Cursor* makeTimeCursor(const CursorProto& cp, Waveform* w);

class OutlinedCursorLabel;

class Cursor : public Component,
               public SettableTooltipClient,
               public Listener<SampleTime>,
               public app::LanguageListener,
               public juce::Label::Listener {
 public:
  Cursor(const CursorProto& d, Waveform* w, int index);
  virtual ~Cursor();
  virtual void init();

  virtual void operator()(const WaveformProto&);
  virtual void operator()(SampleTime t);
  virtual void languageChanged();

  virtual void labelTextChanged(juce::Label*);

  void setText(const String&);
  void setSelected(bool);

  void paint(Graphics& g);
  SampleTime getTime() const;
  bool setDragTime(SampleTime time);
  void setTime(SampleTime time);
  virtual void setTooltip(const String&);

  static const int TIME_CURSOR_INDEX = -1;

  bool isTimeCursor() const { return index_ == TIME_CURSOR_INDEX; }

  const CursorProto& desc() const { return desc_; }

  int index() { return index_; }
  void setIndex(int index) { index_ = index; }
  void layout();
  void setCaption(const String&);
  Waveform* waveform() const { return waveform_; }
  void resizeCaption();
  void selectButtonPressed(bool);
  Component* getCaption();
  static void registerAllTranslations();

 private:
  void layoutCaption();

  Waveform* const waveform_;
  const CriticalSection& lock() const { return waveform_->lock_; }
  CursorProto desc_;
  SampleTime time_;
  int index_;
  juce::Rectangle<int> bounds_;
  int dragX_;
  int mouseDragX_;
  ptr<OutlinedCursorLabel> caption_;
  int captionWidth_;
  bool showSelection_;
  WaveformProto waveDesc_;

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
