#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/base/Trans.h"

TRAN(NONE, "(None)");

namespace rec {
namespace command {

CommandMapTopLevelItem::CommandMapTopLevelItem(CommandMapEditor* owner)
    : owner_(owner) {
  setLinesDrawnForSubItems (false);
  owner_->getChangeBroadcaster()->addChangeListener(this);
}

CommandMapTopLevelItem::~CommandMapTopLevelItem() {
  owner_->getChangeBroadcaster()->removeChangeListener(this);
}

void CommandMapTopLevelItem::changeListenerCallback(ChangeBroadcaster*) {
  DLOG(INFO) << "changeListenerCallback";
  const OpennessRestorer openness(*this);
  clearSubItems();

  StringArray categories(owner_->getCommandManager()->getCommandCategories());
  categories.sort(false);

  for (int i = 0; i < categories.size(); ++i) {
    const String& cat = categories[i];
    const Array<CommandID> commands(owner_->getCommandManager()->
                                    getCommandsInCategory(cat));
    int count = 0;

    for (int j = 0; j < commands.size(); ++j)
      if (owner_->shouldCommandBeIncluded(commands[j]))
        ++count;

    if (count > 0) {
      addSubItem(new CommandMapCategoryItem(owner_, cat));
    } else if (cat != t_NONE) {
      LOG(DFATAL) << "Nothing in category " << str(cat)
                  << ", " << commands.size();
    }
  }
}

}  // namespace command
}  // namespace rec

