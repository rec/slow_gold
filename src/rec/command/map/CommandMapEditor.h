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

class JUCE_API CommandMapEditor : public Component {
 public:
  CommandMapEditor(ApplicationCommandManager& commandManager,
                   ChangeBroadcaster& broadcaster);

  void initialize();

  virtual void addButton(CommandMapEditButton* button) = 0;
  virtual void removeButton(CommandMapEditButton* button) = 0;
  virtual void addChildren(CommandMapItemComponent* comp) = 0;

  virtual CommandEntryWindow* newWindow() = 0;

  /** Destructor. */
  virtual ~CommandMapEditor();

  void setColours(const Colour& mainBackground,
                  const Colour& textColour);

  virtual bool shouldCommandBeIncluded(CommandID commandID);
  virtual bool isCommandReadOnly(CommandID commandID);

  ApplicationCommandManager& getCommandManager() { return commandManager; }
  ChangeBroadcaster& getChangeBroadcaster() { return broadcaster; }
  enum ColourIds {
    backgroundColourId  = 0x100ad00,
    textColourId        = 0x100ad01,
  };

  virtual void parentHierarchyChanged();
  virtual void resized();

 protected:
  void addButton(TextButton*);

  ApplicationCommandManager& commandManager;
  ChangeBroadcaster& broadcaster;
  TreeView tree;
  TextButton resetButton;
  TextButton clearButton;
  TextButton exportButton;
  TextButton importButton;
  TextButton okButton;

  ScopedPointer<CommandMapTopLevelItem> treeItem;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommandMapEditor);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITOR__
