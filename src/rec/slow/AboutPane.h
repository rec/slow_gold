#pragma once

#include "rec/base/base.h"

namespace rec { namespace util { namespace ews { class Authentication; }}}
namespace rec { namespace gui { class CaptionText; }}
namespace rec { namespace gui { class SetterToggle; }}

namespace rec {
namespace slow {

class AboutPane : public Component,
                  public TextEditor::Listener,
                  public juce::ButtonListener {
 public:
  AboutPane(const String& name, const String& versionNumber,
            juce::ModalComponentManager::Callback* callback);
  ~AboutPane() override;

  void textEditorTextChanged(TextEditor&) override;
  void textEditorReturnKeyPressed(TextEditor&) override {}
  void textEditorEscapeKeyPressed(TextEditor&) override {}
  void textEditorFocusLost(TextEditor&) override {}
  void buttonClicked(juce::Button*) override;

  void paint(Graphics& g);
  void visibilityChanged() override;
  bool expired() const;
  bool authenticated() const;

  juce::AttributedString getRightSide() const;
  juce::AttributedString getLeftSide() const;

  static const int WIDTH;
  static const int HEIGHT;

 private:
  juce::AttributedString left_, right_;
  unique_ptr<gui::SetterToggle> displayOnStartup_;
  unique_ptr<ews::Authentication> authentication_;
  unique_ptr<gui::CaptionText> name_, serialNumber_;
  juce::TextButton accept_;
  juce::TextButton close_;
  juce::ModalComponentManager::Callback* callback_;
};

}  // namespace slow
}  // namespace rec
