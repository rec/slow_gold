#pragma once

#include "rec/gui/SimpleLabel.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class WaveformProto;

class OutlinedCursorLabel : public gui::SimpleLabel,
                                                        public DataListener<WaveformProto>,
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

    virtual void editorShown(TextEditor*);
    virtual void editorAboutToBeHidden(TextEditor*);

  private:
    Cursor* cursor_;
    juce::ToggleButton selectButton_;
    bool showSelectionButtons_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(OutlinedCursorLabel);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

