#ifndef __REC_GUI_SETTERTEXT__
#define __REC_GUI_SETTERTEXT__

#include "rec/data/Value.h"
#include "rec/gui/layout/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/data/AddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

static const int CAPTION_SIZE = 50;

class SetterText : public Layout,
                   public data::AddressListener,
                   public TextEditor::Listener {
 public:
  SetterText(const String& name,
             const string& typeName,
             const data::Address& address,
             const String& tip = String::empty,
             const String& caption = String::empty,
             bool useCaption = true,
             Scope scope = FILE_SCOPE)
      : Layout(name, HORIZONTAL),
        data::AddressListener(address, typeName, scope) {
    DCHECK(name.length());
    const String& cap = caption.length() ? caption : name;
    caption_.setName(name + ".caption");
    editor_.setName(name + ".editor");

    setTooltip(tip.length() ? tip : cap);

    if (useCaption) {
      caption_.setText(cap, false);
      addToLayout(&caption_, CAPTION_SIZE);
    }
    addToLayout(&editor_);

    editor_.addListener(this);
  }

  virtual void operator()(const data::Value& v) {
    if (v.has_string_f() && str(v.string_f()) != editor_.getText())
      thread::callAsync(this, &SetterText::setEditorText, str(v.string_f()));
  }


  virtual void setTooltip(const String& newTooltip) {
    Layout::setTooltip(newTooltip);
    editor_.setTooltip(newTooltip);
    caption_.setTooltip(newTooltip);
  }

    void setReadOnly(bool readOnly) {
    if (readOnly != isReadOnly()) {
      editor_.setReadOnly(readOnly);
      editor_.setCaretVisible(!readOnly);
    }
  }

  bool isReadOnly() const { return editor_.isReadOnly(); }

  TextEditor* editor() { return &editor_; }

  virtual void textEditorTextChanged(TextEditor&) {
    setValue(data::Value(str(editor_.getText())));
  }

  virtual void textEditorReturnKeyPressed(TextEditor& editor) {}
  virtual void textEditorEscapeKeyPressed(TextEditor& editor) {}
  virtual void textEditorFocusLost(TextEditor& editor) {}

  void setEditorBackground(const juce::Colour& c) {
    editor_.setColour(juce::TextEditor::backgroundColourId, c);
  }

 protected:
  void setEditorText(String text) {
  	editor_.setText(text, false);
    repaint();
  }

  SimpleLabel caption_;
  TextEditor editor_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterText);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXT__
