#include "rec/gui/CaptionText.h"

namespace rec {
namespace gui {

CaptionText::CaptionText(const String& name,
                         const String& tip,
                         const String& caption,
                         bool useCaption,
                         int captionSize)
    : Panel(name),
      caption_(new SimpleLabel),
      editor_(new TextEditor) {
  DCHECK(name.length());
  const String& cap = caption.length() ? caption : name;
  caption_->setName(name + ".caption");
  editor_->setName(name + ".editor");

  setTooltip(tip.length() ? tip : cap);

  if (useCaption) {
    caption_->setText(cap, juce::dontSendNotification);
    addToPanel(caption_, captionSize);
  }
  addToPanel(editor_);

  editor_->addListener(this);
}

void CaptionText::setTooltip(const String& newTooltip) {
  Panel::setTooltip(newTooltip);
  editor_->setTooltip(newTooltip);
  caption_->setTooltip(newTooltip);
}

void CaptionText::setReadOnly(bool readOnly) {
  if (readOnly != isReadOnly()) {
    editor_->setReadOnly(readOnly);
    editor_->setCaretVisible(!readOnly);
  }
}

void CaptionText::setEditorBackground(const juce::Colour& c) {
  editor_->setColour(juce::TextEditor::backgroundColourId, c);
}

void CaptionText::setEditorText(String text) {
  editor_->setText(text, false);
  repaint();
}

}  // namespace gui
}  // namespace rec
