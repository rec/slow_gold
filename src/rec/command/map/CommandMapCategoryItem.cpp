#include "rec/command/map/CommandMapCategoryItem.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"

namespace rec {
namespace command {

CommandMapCategoryItem::CommandMapCategoryItem(CommandMapEditor& owner_,
                                               const String& name)
    : owner (owner_), categoryName (name) {
}

CommandMapEditorMappingItem* CommandMapCategoryItem::createItemComponent(
    CommandID cmd) const {
  return new CommandMapEditorMappingItem(owner, cmd);
}

void CommandMapCategoryItem::paintItem(Graphics& g, int width, int height) {
  Font f = g.getCurrentFont();
  f.setHeight(height * 0.6f);
  f.setTypefaceStyle("bold");

  g.setFont (f);
  g.setColour (owner.findColour (CommandMapEditor::textColourId));

  g.drawText (categoryName,
              2, 0, width - 2, height,
              Justification::centredLeft, true);
}

void CommandMapCategoryItem::itemOpennessChanged(bool isNowOpen) {
  if (isNowOpen) {
    if (getNumSubItems() == 0) {
      Array <CommandID> commands (owner.getCommandManager().getCommandsInCategory (categoryName));

      for (int i = 0; i < commands.size(); ++i) {
        if (owner.shouldCommandBeIncluded (commands[i]))
          addSubItem (createItemComponent (commands[i]));  // TODO: why?
      }
    }
  } else {
    clearSubItems();
  }
}

}  // namespace command
}  // namespace rec

