#include "rec/gui/SetterText.h"

namespace rec {
namespace gui {

static const int CAPTION_SIZE = 50;

SetterText::SetterText(const String& name,
                       const string& typeName,
                       const data::Address& address,
                       const String& tip,
                       const String& caption,
                       bool useCaption)
    : Panel(name, HORIZONTAL),
      data::AddressListener(address, typeName) {
  DCHECK(name.length());
  const String& cap = caption.length() ? caption : name;
  caption_.setName(name + ".caption");
  editor_.setName(name + ".editor");

  setTooltip(tip.length() ? tip : cap);

  if (useCaption) {
    caption_.setText(cap, juce::dontSendNotification);
    addToPanel(&caption_, CAPTION_SIZE);
  }
  addToPanel(&editor_);

  editor_.addListener(this);
}

void SetterText::operator()(const data::Value& v) {
  if (v.has_string_f() && str(v.string_f()) != editor_.getText())
    setEditorText(str(v.string_f()));
}

void SetterText::setTooltip(const String& newTooltip) {
  Panel::setTooltip(newTooltip);
  editor_.setTooltip(newTooltip);
  caption_.setTooltip(newTooltip);
}

void SetterText::setReadOnly(bool readOnly) {
  if (readOnly != isReadOnly()) {
    editor_.setReadOnly(readOnly);
    editor_.setCaretVisible(!readOnly);
  }
}

void SetterText::textEditorTextChanged(TextEditor&) {
  setValue(str(editor_.getText()));
}

void SetterText::setEditorBackground(const juce::Colour& c) {
  editor_.setColour(juce::TextEditor::backgroundColourId, c);
}

void SetterText::setEditorText(String text) {
  editor_.setText(text, false);
  repaint();
}

}  // namespace gui
}  // namespace rec
