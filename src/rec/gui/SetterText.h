#ifndef __REC_GUI_SETTERTEXT__
#define __REC_GUI_SETTERTEXT__

#include "rec/gui/Layout.h"
#include "rec/util/listener/AddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterText : public Layout,
                   public AddressListener<Proto>,
                   public TextEditor::Listener {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  SetterText(const String& name, const Address& address,
             const String& tip = String::empty,
             const String& caption = String::empty)
      : Layout(HORIZONTAL, true, name),
        AddressListener<Proto>(address),
        caption_(caption + ".caption"),
        editor_(name + ".editor") {
    const String& cap = caption.length() ? caption : name;
    caption_.setText(cap, false);
    editor_.setTooltip(tip.length() ? tip : cap);

    caption_.setText(cap, false);
    caption_.setFont(Font(14.0000f, Font::bold));
    caption_.setJustificationType(juce::Justification::centredRight);
    caption_.setEditable(false, false, false);
    caption_.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    caption_.setColour(juce::TextEditor::backgroundColourId, Colour(0x0));

    addToLayout(&caption_, 70);
    addToLayout(&editor_);

    editor_.addListener(this);
  }

  void setReadOnly(bool readOnly) {
    if (readOnly != isReadOnly()) {
      editor_.setReadOnly(readOnly);
      editor_.setCaretVisible(!readOnly);
    }
  }

  bool isReadOnly() const { return editor_.isReadOnly(); }

  TextEditor* editor() { return &editor_; }

  virtual void textEditorTextChanged (TextEditor& editor) { this->onChange(); }
  virtual void textEditorReturnKeyPressed (TextEditor& editor) {}
  virtual void textEditorEscapeKeyPressed (TextEditor& editor) {}
  virtual void textEditorFocusLost (TextEditor& editor) {}

 protected:
  virtual const Value get() const {
    return string(editor_.getText().toCString());
  }

  virtual void set(const Value& value) {
    if (value.has_string_f()) {
      thread::callAsync(&editor_, &TextEditor::setText,
                        String(value.string_f().c_str()), false);
      util::thread::callAsync(this, &SetterText::repaint);
    }
  }

  void repaint() { Layout::repaint(); }

  juce::Label caption_;
  TextEditor editor_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterText);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXT__
