#ifndef __REC_COMMAND_COMMANDMAPEDITORMAPPINGITEM__
#define __REC_COMMAND_COMMANDMAPEDITORMAPPINGITEM__

#include "rec/command/map/MapItemComponent.h"

namespace rec {
namespace command {

class MapItem : public TreeViewItem {
 public:
  MapItem(Editor* owner, CommandID commandID)
      : owner_(owner), commandID_(commandID) {
  }

  String getUniqueName() const { return String((int) commandID_) + "_id"; }
  bool mightContainSubItems() { return false; }
  int getItemHeight() const { return 20; }

  Component* createItemComponent() {
    return new MapItemComponent(owner_, commandID_);
  }

 private:
  Editor* owner_;
  const CommandID commandID_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MapItem);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITORMAPPINGITEM__
