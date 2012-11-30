#ifndef __REC_COMMAND_COMMANDMAPTOPLEVELITEM__
#define __REC_COMMAND_COMMANDMAPTOPLEVELITEM__

#include "rec/command/map/CommandMapCategoryItem.h"

namespace rec {
namespace command {

class CommandMapTopLevelItem : public TreeViewItem, public ChangeListener {
 public:
  explicit CommandMapTopLevelItem(CommandMapEditor*);
  ~CommandMapTopLevelItem();

  bool mightContainSubItems() { return true; }
  String getUniqueName() const { return "keys"; }

  void changeListenerCallback(ChangeBroadcaster*);

 protected:
  CommandMapEditor* owner_;
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPTOPLEVELITEM__
