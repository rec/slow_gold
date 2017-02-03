#pragma once

#include "rec/base/base.h"

namespace rec {
namespace command {

class Editor;
class EditButton;

typedef std::pair<int, EditButton*> MenuCallback;

class EditButton : public juce::Button {
 public:
  EditButton(Editor* editor, CommandID id, const String& keyName, int keyNum);
  void paintButton(Graphics& g, bool /*isOver*/, bool /*isDown*/);
  void clicked();

  void fitToContent (const int h) noexcept;
  Editor* getEditor() { return editor_; }

  const CommandID id_;
  const int keyNum_;

 private:
  Editor* const editor_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditButton);
};

}  // namespace command
}  // namespace rec

