#ifndef __REC_COMMAND_COMMANDMAPEDITOR__
#define __REC_COMMAND_COMMANDMAPEDITOR__

#include "rec/util/Deletable.h"
#include "rec/util/Listener.h"

using namespace juce;

namespace rec {
namespace command {

class CommandMapEditButton;
class CommandMapTopLevelItem;
class CommandMapItemComponent;
class CommandEntryWindow;

class CommandMapEditor : public Component, public ButtonListener,
                         Listener<const File&> {
 public:
  CommandMapEditor(ApplicationCommandManager* commandManager,
                   ChangeBroadcaster* broadcaster);
  virtual ~CommandMapEditor();

  void initialize();
  virtual void operator()(const File&);

  virtual void addButton(CommandMapEditButton* button) = 0;
  virtual void removeButton(CommandMapEditButton* button) = 0;
  virtual void addChildren(CommandMapItemComponent* comp) = 0;
  virtual const String name() const = 0;
  virtual bool isValid(const string&) const = 0;
  virtual const String getDescription(const string&) const = 0;
  virtual CommandID getCommand(const string&) = 0;
  virtual void removeKey(CommandID, int keyNum) = 0;
  virtual void removeKey(const string&) = 0;
  virtual void addKey(CommandID, const string&, int keyIndex) = 0;

  virtual void doReset() {}
  virtual void doClear() {}
  virtual void doExport(const File&) {}
  virtual void doImport(const File&) {}

  virtual CommandEntryWindow* newWindow() = 0;
  const String getKeyMessage(const string& key);

  virtual void buttonClicked(Button* button);

  void setColours(const Colour& mainBackground,
                  const Colour& textColour);

  virtual bool shouldCommandBeIncluded(CommandID commandID);
  virtual bool isCommandReadOnly(CommandID commandID);

  ApplicationCommandManager* getCommandManager() { return commandManager_; }
  ChangeBroadcaster* getChangeBroadcaster() { return broadcaster_; }

  enum ColourIds {
    backgroundColourId  = 0x100ad00,
    textColourId        = 0x100ad01,
  };

  virtual void parentHierarchyChanged();
  virtual void resized();

  // Callbacks from the buttons.
  void resetButton();
  void clearButton();
  void exportButton();
  void importButton();
  void okButton();
  void resetTreeItem();

 protected:
  void addButton(TextButton*);

  ApplicationCommandManager* commandManager_;
  ChangeBroadcaster* broadcaster_;
  TreeView tree;
  TextButton resetButton_;
  TextButton clearButton_;
  TextButton exportButton_;
  TextButton importButton_;
  TextButton okButton_;

  ptr<CommandMapTopLevelItem> treeItem_;
  bool expectingExport_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommandMapEditor);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITOR__
