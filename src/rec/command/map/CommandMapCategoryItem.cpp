#include "rec/command/map/CommandMapCategoryItem.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"

namespace rec {
namespace command {

CommandMapCategoryItem::CommandMapCategoryItem(CommandMapEditor* owner,
                                               const String& name)
    : owner_(owner), categoryName_(name) {
}

CommandMapEditorMappingItem* CommandMapCategoryItem::createItemComponent(
    CommandID cmd) const {
  return new CommandMapEditorMappingItem(owner_, cmd);
}

void CommandMapCategoryItem::paintItem(Graphics& g, int width, int height) {
  Font f = g.getCurrentFont();
  f.setHeight(height * 0.6f);
  f.setTypefaceStyle("bold");

  g.setFont(f);
  g.setColour(owner_->findColour(CommandMapEditor::textColourId));

  g.drawText(categoryName_,
             2, 0, width - 2, height,
             Justification::centredLeft, true);
}

void CommandMapCategoryItem::itemOpennessChanged(bool isNowOpen) {
  if (!isNowOpen) {
    clearSubItems();
  } else if (getNumSubItems() == 0) {
    Array<CommandID> commands(owner_->getCommandManager()->
                              getCommandsInCategory(categoryName_));

    for (int i = 0; i < commands.size(); ++i) {
      if (owner_->shouldCommandBeIncluded(commands[i]))
        addSubItem(createItemComponent(commands[i]));  // TODO: why?
    }
  }
}

}  // namespace command
}  // namespace rec

