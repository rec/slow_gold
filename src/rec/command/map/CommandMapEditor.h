#ifndef __REC_COMMAND_COMMANDMAPEDITOR__
#define __REC_COMMAND_COMMANDMAPEDITOR__

#include "rec/base/base.h"

using namespace juce;

namespace rec {
namespace command {

class CommandMapEditButton;
class CommandMapTopLevelItem;
class CommandMapItemComponent;
class CommandEntryWindow;

class CommandMapEditor : public Component, public ButtonListener {
 public:
  CommandMapEditor(ApplicationCommandManager& commandManager,
                   ChangeBroadcaster& broadcaster);
  virtual ~CommandMapEditor();

  void initialize();

  virtual void addButton(CommandMapEditButton* button) = 0;
  virtual void removeButton(CommandMapEditButton* button) = 0;
  virtual void addChildren(CommandMapItemComponent* comp) = 0;
  virtual void buttonClicked(Button* button);

  virtual CommandEntryWindow* newWindow() = 0;

  void setColours(const Colour& mainBackground,
                  const Colour& textColour);

  virtual bool shouldCommandBeIncluded(CommandID commandID);
  virtual bool isCommandReadOnly(CommandID commandID);

  ApplicationCommandManager& getCommandManager() { return commandManager_; }
  ChangeBroadcaster& getChangeBroadcaster() { return broadcaster_; }
  enum ColourIds {
    backgroundColourId  = 0x100ad00,
    textColourId        = 0x100ad01,
  };

  virtual void parentHierarchyChanged();

  // Callbacks from the buttons.
  virtual void resized();
  virtual void reset() {}
  virtual void clear() {}
  virtual void exportSetting() {}
  virtual void import() {}
  virtual void ok() {}

 protected:
  void addButton(TextButton*);

  ApplicationCommandManager& commandManager_;
  ChangeBroadcaster& broadcaster_;
  TreeView tree;
  TextButton resetButton_;
  TextButton clearButton_;
  TextButton exportButton_;
  TextButton importButton_;
  TextButton okButton_;

  ptr<CommandMapTopLevelItem> treeItem_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommandMapEditor);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITOR__
