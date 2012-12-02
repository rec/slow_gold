#ifndef __REC_COMMAND_COMMANDMAPTOPLEVELITEM__
#define __REC_COMMAND_COMMANDMAPTOPLEVELITEM__

#include "rec/base/base.h"

namespace rec {
namespace command {

class TopLevelItem : public TreeViewItem, public ChangeListener {
 public:
  explicit TopLevelItem(Editor*);
  ~TopLevelItem();

  bool mightContainSubItems() { return true; }
  String getUniqueName() const { return "keys"; }

  void changeListenerCallback(ChangeBroadcaster*);

 protected:
  Editor* owner_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(TopLevelItem);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPTOPLEVELITEM__
