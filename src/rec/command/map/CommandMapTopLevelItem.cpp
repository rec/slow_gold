#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/base/Trans.h"

TRAN(NONE, "(None)");

namespace rec {
namespace command {

CommandMapTopLevelItem::CommandMapTopLevelItem(CommandMapEditor& owner_)
    : owner (owner_) {
  setLinesDrawnForSubItems (false);
  owner.getChangeBroadcaster()->addChangeListener(this);
}

CommandMapTopLevelItem::~CommandMapTopLevelItem() {
  owner.getChangeBroadcaster()->removeChangeListener(this);
}

void CommandMapTopLevelItem::changeListenerCallback(ChangeBroadcaster*) {
  const OpennessRestorer openness(*this);
  clearSubItems();

  const StringArray categories(owner.getCommandManager()->getCommandCategories());

  for (int i = 0; i < categories.size(); ++i) {
    const String& cat = categories[i];
    const Array<CommandID> commands(owner.getCommandManager()->
                                    getCommandsInCategory(cat));
    int count = 0;

    for (int j = 0; j < commands.size(); ++j)
      if (owner.shouldCommandBeIncluded(commands[j]))
        ++count;

    if (count > 0) {
      addSubItem(new CommandMapCategoryItem(&owner, cat));
    } else if (cat != t_NONE) {
      LOG(DFATAL) << "Nothing in category " << str(cat)
                  << ", " << commands.size();
    }
  }
}

}  // namespace command
}  // namespace rec

