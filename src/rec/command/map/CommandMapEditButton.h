#ifndef __REC_COMMAND_COMMANDMAPEDITBUTTON__
#define __REC_COMMAND_COMMANDMAPEDITBUTTON__

#include "rec/command/map/CommandEntryWindow.h"

namespace rec {
namespace command {

class CommandMapEditor;

class CommandMapEditButton  : public juce::Button {
 public:
  CommandMapEditButton(CommandMapEditor& owner_, const CommandID commandID_,
                       const String& keyName,
                       const int keyNum_);

  void addCommand();
  void removeCommand();

  void paintButton(Graphics& g, bool /*isOver*/, bool /*isDown*/);
  static void menuCallback (int result, CommandMapEditButton* button);

  void clicked();

  void fitToContent (const int h) noexcept;

  const CommandID commandID;
  const int keyNum;

  CommandEntryWindow* getCommandEntryWindow() { return currentCommandEntryWindow; }
  void setCommandEntryWindow(CommandEntryWindow* window = nullptr) { currentCommandEntryWindow = window; }
  CommandMapEditor& getOwner() { return owner; }
  static void translateAll();

 private:
  CommandMapEditor& owner;
  juce::ScopedPointer<CommandEntryWindow> currentCommandEntryWindow;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CommandMapEditButton);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITBUTTON__
