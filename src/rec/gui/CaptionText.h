#pragma once

#include "rec/gui/proto/Panel.h"
#include "rec/gui/SimpleLabel.h"

namespace rec {
namespace gui {

static const int CAPTION_SIZE = 50;

class CaptionText : public Panel, public TextEditor::Listener {
 public:
  CaptionText(const String& name,
              const String& tip = String::empty,
              const String& caption = String::empty,
              bool useCaption = true,
              int captionSize = CAPTION_SIZE);
  virtual ~CaptionText() {}

  virtual void setTooltip(const String& newTooltip);
  void setReadOnly(bool readOnly);

  bool isReadOnly() const { return editor_->isReadOnly(); }

  TextEditor* editor() { return editor_; }

  void textEditorTextChanged(TextEditor&) override {}
  void textEditorReturnKeyPressed(TextEditor&) override {}
  void textEditorEscapeKeyPressed(TextEditor&) override {}
  void textEditorFocusLost(TextEditor&) override {}

  void setEditorBackground(const juce::Colour&);

 protected:
  void setEditorText(String);

  SimpleLabel* caption_;
  TextEditor* editor_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CaptionText);
};

}  // namespace gui
}  // namespace rec
