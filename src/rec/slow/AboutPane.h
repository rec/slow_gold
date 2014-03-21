#pragma once

#include "rec/base/base.h"

namespace rec { namespace app { class Authentication; }}
namespace rec { namespace gui { class CaptionText; }}
namespace rec { namespace gui { class SetterToggle; }}

namespace rec {
namespace slow {

class AboutPane : public Component, public TextEditor::Listener {
 public:
  AboutPane(const String& name, const String& versionNumber);
  ~AboutPane() override;

  void textEditorTextChanged(TextEditor&) override;
  void textEditorReturnKeyPressed(TextEditor&) override {}
  void textEditorEscapeKeyPressed(TextEditor&) override {}
  void textEditorFocusLost(TextEditor&) override {}

  void paint(Graphics& g);
  void visibilityChanged() override;
  bool expired() const;

  juce::AttributedString getRightSide() const;
  juce::AttributedString getLeftSide() const;

  static const int WIDTH;
  static const int HEIGHT;

 private:
  juce::AttributedString left_, right_;
  unique_ptr<gui::SetterToggle> displayOnStartup_;
  unique_ptr<app::Authentication> authentication_;
  unique_ptr<gui::CaptionText> name_, serialNumber_;
  juce::TextButton accept_;
};

}  // namespace slow
}  // namespace rec
