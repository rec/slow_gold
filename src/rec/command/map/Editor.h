#ifndef __REC_COMMAND_COMMANDMAPEDITOR__
#define __REC_COMMAND_COMMANDMAPEDITOR__

#include "rec/util/Deletable.h"
#include "rec/util/Listener.h"

using namespace juce;

namespace rec {
namespace command {

class CommandMap;
class EditButton;
class TopLevelItem;
class MapItemComponent;

class Editor : public Component, public ButtonListener,
               public Listener<const File&> {
 public:
  Editor(ApplicationCommandManager*, CommandMap*);
  virtual ~Editor();

  void initialize();
  virtual void operator()(const File&);

  virtual const String name() const = 0;
  virtual bool isValid(const string&) const = 0;
  virtual const String getDescription(const string&) const = 0;
  virtual void removeKey(CommandID, int keyNum) = 0;
  virtual void removeKey(const string&) = 0;
  virtual void addKey(CommandID, const string&, int keyIndex) = 0;

  typedef juce::Array<string> KeyArray;
  virtual KeyArray getKeys(CommandID) = 0;
  virtual const String getWindowTitle() const = 0;
  virtual const String getKeyMessage(const string&);

  virtual CommandID getCommand(const string&);
  void addChildren(MapItemComponent*);

  void addButton(EditButton* b);
  void removeButton(EditButton*);
  void buttonMenuCallback(int result, EditButton*);

  void setNewKey(EditButton* button, const string& newKey,
                 bool dontAskUser);

  juce::AlertWindow* newWindow();

  virtual void doReset() {}
  virtual void doClear() {}
  virtual void doExport(const File&) {}
  virtual void doImport(const File&) {}

  virtual void buttonClicked(Button* button);

  void setColours(const Colour& mainBackground,
                  const Colour& textColour);

  virtual bool shouldCommandBeIncluded(CommandID commandID);
  virtual bool isCommandReadOnly(CommandID commandID);

  ApplicationCommandManager* getCommandManager() { return commandManager_; }
  ChangeBroadcaster* getChangeBroadcaster() { return commandMap_; }

  enum ColourIds {
    backgroundColourId  = 0x100ad00,
    textColourId        = 0x100ad01,
  };

  static const int MAX_NUM_ASSIGNMENTS = 3;

  virtual void parentHierarchyChanged();
  virtual void resized();

  // Callbacks from the buttons.
  void resetButton();
  void clearButton();
  void exportButton();
  void importButton();
  void okButton();

  void setKey(const string&);

  void assignNewKey(EditButton* button, const string& key);

 protected:
  typedef map<CommandID, MapItem*> MapItemMap;

  ApplicationCommandManager* commandManager_;
  CommandMap* commandMap_;
  MapItemMap mapItemMap_;

  TreeView tree;
  TextButton resetButton_;
  TextButton clearButton_;
  TextButton exportButton_;
  TextButton importButton_;
  TextButton okButton_;

  ptr<juce::AlertWindow> entryWindow_;
  EditButton* lastEditButton_;

  ptr<TopLevelItem> topLevelItem_;
  bool expectingExport_;

  string key_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Editor);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITOR__
