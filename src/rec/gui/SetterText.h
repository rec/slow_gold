#ifndef __REC_GUI_SETTERTEXT__
#define __REC_GUI_SETTERTEXT__

#include "rec/gui/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/util/listener/ProtoAddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterText : public Layout,
                   public ProtoAddressListener,
                   public TextEditor::Listener {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;

  SetterText(const String& name, const Address& address,
             const String& tip = String::empty,
             const String& caption = String::empty)
      : Layout(name, HORIZONTAL),
        ProtoAddressListener(address),
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

  virtual void textEditorTextChanged (TextEditor& editor) {
    this->updatePersistentData();
  }
  virtual void textEditorReturnKeyPressed (TextEditor& editor) {}
  virtual void textEditorEscapeKeyPressed (TextEditor& editor) {}
  virtual void textEditorFocusLost (TextEditor& editor) {}

 protected:
  virtual const Value get() const {
    return str(editor_.getText());
  }

  virtual void set(const Value& value) {
    if (value.has_string_f()) {
      thread::callAsync(&editor_, &TextEditor::setText,
                        String(value.string_f().c_str()), false);
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
