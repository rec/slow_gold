#ifndef __REC_GUI_SETTERTEXT__
#define __REC_GUI_SETTERTEXT__

#include "rec/data/Value.h"
#include "rec/gui/proto/Panel.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/data/AddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterText : public Panel,
                   public data::AddressListener,
                   public TextEditor::Listener {
 public:
  SetterText(const String& name,
             const string& typeName,
             const data::Address& address,
             const String& tip = String::empty,
             const String& caption = String::empty,
             bool useCaption = true);
  virtual ~SetterText() {}

  virtual void operator()(const data::Value& v);
  virtual void setTooltip(const String& newTooltip);
  void setReadOnly(bool readOnly);

  bool isReadOnly() const { return editor_.isReadOnly(); }

  TextEditor* editor() { return &editor_; }

  virtual void textEditorTextChanged(TextEditor&);
  virtual void textEditorReturnKeyPressed(TextEditor&) {}
  virtual void textEditorEscapeKeyPressed(TextEditor&) {}
  virtual void textEditorFocusLost(TextEditor&) {}

  void setEditorBackground(const juce::Colour&);

 protected:
  void setEditorText(String);

  SimpleLabel caption_;
  TextEditor editor_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterText);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXT__
