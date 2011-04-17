#ifndef __REC_SLOW_MENUS__
#define __REC_SLOW_MENUS__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Menus : public MenuBarModel {
 public:
  Menus(Instance* i) : instance_(i) {}

  virtual const StringArray getMenuBarNames();
  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& name);
  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {}

 private:
  void add(PopupMenu* m, CommandID c) {
    instance_->target_.addCommandItem(m, c);
  }

  Instance* instance_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Menus);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_MENUS__
