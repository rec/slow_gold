#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/base/Trans.h"

namespace rec {
namespace command {

namespace {

Trans RESET_TO_DEFAULTS("Reset to defaults");
Trans SURE_YOU_RESET("Are you sure you want to reset all the key-mappings to their default state?");
Trans RESET("Reset");

}

CommandMapTopLevelItem::CommandMapTopLevelItem(CommandMapEditor& owner_)
    : owner (owner_) {
  setLinesDrawnForSubItems (false);
  owner.getChangeBroadcaster().addChangeListener (this);
}

CommandMapTopLevelItem::~CommandMapTopLevelItem() {
  owner.getChangeBroadcaster().removeChangeListener (this);
}

void CommandMapTopLevelItem::changeListenerCallback(ChangeBroadcaster*) {
  const OpennessRestorer openness (*this);
  clearSubItems();

  const StringArray categories (owner.getCommandManager().getCommandCategories());

  for (int i = 0; i < categories.size(); ++i)
  {
      const String& cat = categories[i];
      const Array <CommandID> commands (owner.getCommandManager().getCommandsInCategory (cat));
      int count = 0;

      for (int j = 0; j < commands.size(); ++j)
          if (owner.shouldCommandBeIncluded (commands[j]))
              ++count;

      if (count > 0)
          addSubItem (new CommandMapCategoryItem(owner, cat));
      else if (cat != trans("(None)")) {
        LOG(DFATAL) << "Nothing in category " << str(cat)
                   << ", " << commands.size();
      }

  }
}

void CommandMapTopLevelItem::buttonClicked (Button*)
{
  AlertWindow::showOkCancelBox(
      AlertWindow::QuestionIcon,
      RESET_TO_DEFAULTS,
      SURE_YOU_RESET,
      RESET,
      String::empty,
      &owner,
      ModalCallbackFunction::forComponent (resetToDefaultsCallback, &owner));
}

void CommandMapTopLevelItem::translateAll() {
  RESET_TO_DEFAULTS.translate();
  SURE_YOU_RESET.translate();
  RESET.translate();
}

}  // namespace command
}  // namespace rec

