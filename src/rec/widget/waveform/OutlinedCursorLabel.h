#ifndef __REC_WIDGET_WAVEFORM_OUTLINEDCURSORLABEL__
#define __REC_WIDGET_WAVEFORM_OUTLINEDCURSORLABEL__

#include "rec/gui/SimpleLabel.h"
#include "rec/util/DataListener.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class WaveformProto;

class OutlinedCursorLabel : public gui::SimpleLabel,
                            public GlobalDataListener<WaveformProto>,
                            juce::Button::Listener {
 public:
  explicit OutlinedCursorLabel(Cursor*);
  virtual ~OutlinedCursorLabel();

  void setSelected(bool);
  virtual void operator()(const WaveformProto&);

  virtual void paint(Graphics&);
  virtual void buttonClicked(juce::Button*);

  Cursor* getCursor() const { return cursor_; }
  virtual void resized();

  virtual void textEditorTextChanged(TextEditor&);

  void showButtons(WaveformProto);

 private:
  Cursor* cursor_;
  juce::ToggleButton selectButton_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(OutlinedCursorLabel);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_OUTLINEDCURSORLABEL__
