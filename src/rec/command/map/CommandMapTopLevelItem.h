#ifndef __REC_COMMAND_COMMANDMAPTOPLEVELITEM__
#define __REC_COMMAND_COMMANDMAPTOPLEVELITEM__

#include "rec/command/map/CommandMapCategoryItem.h"

namespace rec {
namespace command {

class CommandMapTopLevelItem : public TreeViewItem,
                               public ChangeListener,
                               public ButtonListener {
public:
  explicit CommandMapTopLevelItem (CommandMapEditor&);
  ~CommandMapTopLevelItem();

    bool mightContainSubItems()       { return true; }
    String getUniqueName() const      { return "keys"; }

  void changeListenerCallback (ChangeBroadcaster*);
  static void resetToDefaultsCallback(int result, CommandMapEditor* owner) {}

  void buttonClicked (Button*);
  static void registerAllTranslations();

 protected:
  CommandMapEditor& owner;
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPTOPLEVELITEM__
