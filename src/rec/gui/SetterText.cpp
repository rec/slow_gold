#include "rec/gui/SetterText.h"

namespace rec {
namespace gui {

SetterText::SetterText(const String& name,
                       const data::Address& address,
                       const String& tip,
                       const String& caption,
                       bool useCaption,
                       int captionSize)
    : CaptionText(name, tip, caption, useCaption, captionSize),
      data::AddressListener(address) {
}

void SetterText::operator()(const data::Value& v) {
  if (v.has_string_f() && str(v.string_f()) != editor_->getText())
    setEditorText(str(v.string_f()));
}

void SetterText::textEditorTextChanged(TextEditor&) {
  setValue(str(editor_->getText()));
}

}  // namespace gui
}  // namespace rec
