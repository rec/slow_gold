#ifndef __REC_GUI_SETTERTEXT__
#define __REC_GUI_SETTERTEXT__

#include "rec/data/Value.h"
#include "rec/gui/layout/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/util/listener/DataListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterText : public Layout,
                   public DataListener<Proto>,
                   public TextEditor::Listener {
 public:
  SetterText(const String& name,
             const data::Address& address,
             const String& tip = String::empty,
             const String& caption = String::empty)
      : Layout(name, HORIZONTAL),
        DataListener<Proto>(address),
        caption_(caption + ".caption"),
        editor_(name + ".editor") {
    const String& cap = caption.length() ? caption : name;
    caption_.setText(cap, false);
    editor_.setTooltip(tip.length() ? tip : cap);

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

  virtual void textEditorTextChanged(TextEditor&) {
    this->setValue(str(editor_.getText()));
  }
  virtual void textEditorReturnKeyPressed(TextEditor& editor) {}
  virtual void textEditorEscapeKeyPressed(TextEditor& editor) {}
  virtual void textEditorFocusLost(TextEditor& editor) {}

 protected:
  virtual void onDataChange(const Proto&) {
    const data::Value value = this->getValue();
    if (value.has_string_f()) {
      thread::callAsync(&editor_, &TextEditor::setText,
                        str(value.string_f()), false);
      util::thread::callAsync(this, &SetterText::repaint);
    }
  }

  void repaint() { Layout::repaint(); }

  SimpleLabel caption_;
  TextEditor editor_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterText);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXT__
