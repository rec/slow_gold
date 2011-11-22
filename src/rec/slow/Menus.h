#ifndef __REC_SLOW_MENUS__
#define __REC_SLOW_MENUS__

#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"

namespace rec {
namespace slow {

class Instance;

class Menus : public MenuBarModel, public HasInstance, public Listener<None> {
 public:
  Menus(Instance* i);

  virtual const StringArray getMenuBarNames();
  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& name);
  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {}
  virtual void operator()(None) { menuItemsChanged(); }

  void addCommandItem(PopupMenu*, CommandID, bool enable = true,
                      const String& name = String::empty);
 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Menus);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_MENUS__
