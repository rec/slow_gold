#ifndef __REC_SLOW_MENUS__
#define __REC_SLOW_MENUS__

#include "rec/slow/HasInstance.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace slow {

struct Instance;

class Menus : public MenuBarModel, public HasInstance {
 public:
  Menus(Instance* i);

  virtual const StringArray getMenuBarNames();
  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& name);
  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {}
  void add(PopupMenu*, command::Command::Type, bool enable = true);

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Menus);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_MENUS__
