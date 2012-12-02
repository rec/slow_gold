#ifndef __REC_COMMAND_COMMANDMAPEDITBUTTON__
#define __REC_COMMAND_COMMANDMAPEDITBUTTON__

#include "rec/command/map/EntryWindow.h"

namespace rec {
namespace command {

class Editor;

class EditButton  : public juce::Button {
 public:
  EditButton(Editor& owner_, const CommandID commandID_,
                       const String& keyName,
                       const int keyNum_);
  void paintButton(Graphics& g, bool /*isOver*/, bool /*isDown*/);
  void clicked();

  void fitToContent (const int h) noexcept;

  const CommandID commandID;
  const int keyNum;

  Editor& getOwner() { return owner; }

 private:
  Editor& owner;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditButton);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITBUTTON__
