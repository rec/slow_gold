#ifndef __REC_COMMAND_COMMANDMAPEDITORMAPPINGITEM__
#define __REC_COMMAND_COMMANDMAPEDITORMAPPINGITEM__

#include "rec/command/map/CommandMapItemComponent.h"

namespace rec {
namespace command {

class CommandMapEditorMappingItem : public TreeViewItem {
 public:
  CommandMapEditorMappingItem(CommandMapEditor* owner, CommandID commandID)
      : owner_(owner), commandID_(commandID) {
  }

  String getUniqueName() const { return String((int) commandID_) + "_id"; }
  bool mightContainSubItems() { return false; }
  int getItemHeight() const { return 20; }

  Component* createItemComponent() {
    return new CommandMapItemComponent(owner_, commandID_);
  }

 private:
  CommandMapEditor* owner_;
  const CommandID commandID_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CommandMapEditorMappingItem);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITORMAPPINGITEM__
