#include "rec/command/map/TopLevelItem.h"

#include "rec/base/Trans.h"
#include "rec/command/map/CategoryItem.h"

TRAN(NONE, "(None)");

namespace rec {
namespace command {

TopLevelItem::TopLevelItem(Editor* owner)
    : owner_(owner) {
  setLinesDrawnForSubItems(false);
  owner_->getChangeBroadcaster()->addChangeListener(this);
}

TopLevelItem::~TopLevelItem() {
  owner_->getChangeBroadcaster()->removeChangeListener(this);
}

static void fillTopLevelItem(Editor* editor, juce::TreeView* top) {
  StringArray categories(editor->getCommandManager()->getCommandCategories());
  categories.sort(false);

  for (int i = 0; i < categories.size(); ++i) {
    const String& cat = categories[i];
    const Array<CommandID> commands(editor->getCommandManager()->
                                    getCommandsInCategory(cat));
    int count = 0;

    for (int j = 0; j < commands.size(); ++j)
      if (editor->shouldCommandBeIncluded(commands[j]))
        ++count;

    if (count > 0) {
      top->addSubItem(new CategoryItem(editor, cat));
    } else if (cat != t_NONE) {
      LOG(DFATAL) << "Nothing in category " << str(cat)
                  << ", " << commands.size();
    }
  }
}


void TopLevelItem::changeListenerCallback(ChangeBroadcaster*) {
  DLOG(INFO) << "changeListenerCallback";
  const OpennessRestorer openness(*this);
  clearSubItems();
  fillTopLevelItem(owner_, this);
}

}  // namespace command
}  // namespace rec

