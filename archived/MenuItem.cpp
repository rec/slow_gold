#include "rec/slow/MenuItem.h"

#include "rec/command/CommandRecordTable.h"

namespace rec {
namespace slow {

void MenuItem::addFull(PopupMenu* m, command::CommandRecordTable* table,
                       ApplicationCommandManager* applicationCommandManager) {
  CommandRecord* cr = commandRecordTable()->find(id_);
  if (!cr) {
    LOG(DFATAL) << "no info for " << CommandIDEncoder::commandIDName(id_);
    return;
  }
  ApplicationCommandInfo* info = cr->getInfo();

  if (name_.length())
    info->shortName = name;
  else if (cr->setter_)
    info->shortName = str(cr->setter_->menuName());

  if (!info->shortName.length()) {
    LOG(ERROR) << "No name for " << CommandIDEncoder::commandIDName(id_);
    info->shortName = "(error)";
  }
  if (flags_ >= 0)
    info->flags = flags_;

  info->setActive(enable_ == ENABLE);
  menu_->addCommandItem(applicationCommandManager(), id_);
}

}  // namespace slow
}  // namespace rec
