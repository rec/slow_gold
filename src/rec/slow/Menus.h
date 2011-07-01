#ifndef __REC_SLOW_MENUS__
#define __REC_SLOW_MENUS__

#include "rec/slow/HasInstance.h"
#include "rec/slow/LoopCommands.h"

namespace rec {
namespace slow {

struct Instance;

class Menus : public MenuBarModel, public HasInstance {
 public:
  Menus(Instance* i);

  virtual const StringArray getMenuBarNames();
  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& name);
  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {}
  void add(PopupMenu*, Command, bool enable = true);

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Menus);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_MENUS__
