#ifndef __REC_COMMAND_COMMANDMAPEDITBUTTON__
#define __REC_COMMAND_COMMANDMAPEDITBUTTON__

#include "rec/base/base.h"

namespace rec {
namespace command {

class Editor;
class EditButton;

typedef std::pair<int, EditButton*> MenuCallback;

class EditButton : public juce::Button {
 public:
  EditButton(Editor* editor, CommandID commandID_, const String& keyName,
             int keyNum_);
  void paintButton(Graphics& g, bool /*isOver*/, bool /*isDown*/);
  void clicked();

  void fitToContent (const int h) noexcept;
  Editor* getEditor() { return editor_; }

  const CommandID commandID;
  const int keyNum;

 private:
  Editor* const editor_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditButton);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITBUTTON__
