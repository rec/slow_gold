#ifndef __REC_COMMAND_MAP_EDITOR__
#define __REC_COMMAND_MAP_EDITOR__

#include <map>

#include "rec/util/Deletable.h"
#include "rec/util/Listener.h"
#include "rec/command/map/EditButton.h"

using namespace juce;

namespace rec {
namespace command {

class CommandMap;
class EditButton;
class MapItem;
class MapItemComponent;

class Editor : public Component,
               public ButtonListener,
               public Listener<const File&> {
 public:
  Editor(ApplicationCommandManager*, CommandMap*);
  virtual ~Editor();

  void initialize();
  virtual void operator()(const File&);

  virtual const String name() const = 0;
  virtual bool isValid(const string&) const = 0;
  virtual const String getDescription(const string&) const = 0;
  virtual void removeKeyAtIndex(CommandID, int keyNum);
  virtual void removeKey(const string&);
  virtual void addKey(CommandID, const string&, int keyIndex);

  typedef juce::Array<string> KeyArray;
  virtual KeyArray getKeys(CommandID);
  virtual const String getWindowTitle() const = 0;
  virtual const String getKeyMessage(const string&);

  virtual CommandID getCommand(const string&);
  void addChildren(MapItemComponent*);

  void addButton(EditButton* b);
  void removeButton(EditButton*);
  void buttonMenuCallback(EditButton*, int result);

  void setNewKey(EditButton* button, const string& newKey);

  juce::AlertWindow* newWindow();

  virtual void reset(int returnValue);
  virtual void clear(int returnValue);
  virtual void exportToFile(const File&);
  virtual void importFromFile(const File&);

  virtual void buttonClicked(Button* button);

  void setColours(const Colour& mainBackground,
                  const Colour& textColour);

  virtual bool shouldCommandBeIncluded(CommandID commandID);
  virtual bool isCommandReadOnly(CommandID commandID);

  ApplicationCommandManager* getCommandManager() { return commandManager_; }
  ChangeBroadcaster* getChangeBroadcaster();

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
  void keyChosen(EditButton* button, int result);

  void assignNewKey(EditButton* button, const string& key, int result = 1);
  bool wasChanged() const { return wasChanged_; }

 protected:
  ptr<juce::AlertWindow> entryWindow_;

 private:
  typedef std::map<CommandID, MapItem*> MapItemMap;

  void fillTopLevelItem();
  bool commandHasFlags(CommandID, int flags) const;

  ApplicationCommandManager* commandManager_;
  CommandMap* commandMap_;
  MapItemMap mapItemMap_;

  TreeView tree_;
  TextButton resetButton_;
  TextButton clearButton_;
  TextButton exportButton_;
  TextButton importButton_;
  TextButton okButton_;

  EditButton* lastEditButton_;

  ptr<juce::TreeViewItem> topLevelItem_;
  bool expectingExport_;

  string key_;
  bool wasChanged_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Editor);
};

inline string toString(const KeyPress& kp) {
  return str(kp.getTextDescription());
}

inline KeyPress keyPressFromString(const string& s) {
  return KeyPress::createFromDescription(str(s));
}

inline MidiMessage midiFromString(const string& s) {
  return MidiMessage(s.data(), s.size());
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MAP_EDITOR__
