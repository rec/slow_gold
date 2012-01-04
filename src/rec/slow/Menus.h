#ifndef __REC_SLOW_MENUS__
#define __REC_SLOW_MENUS__

#include "rec/data/DataListener.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"

namespace rec {
namespace slow {

class GuiSettings;
class Instance;
class MenuMaker;

class Menus : public MenuBarModel, public HasInstance,
              public Listener<None>,
              public DataListener<GuiSettings> {
 public:
  Menus(Instance* i);

  virtual const StringArray getMenuBarNames();
  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& name);
  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {}
  virtual void operator()(None) { menuItemsChanged(); }
  virtual void operator()(const GuiSettings&);

 private:
  void setMenuMaker(bool isAdvanced);

  ptr<MenuMaker> menuMaker_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Menus);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_MENUS__
