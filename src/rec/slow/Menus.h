#ifndef __REC_SLOW_MENUS__
#define __REC_SLOW_MENUS__

#include "rec/data/DataListener.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace slow {

class GuiSettings;
class Instance;
class MenuMaker;
class IsWholeSong;

class Menus : public MenuBarModel,
              public HasInstance,
              public GlobalDataListener<GuiSettings> {
 public:
  Menus(Instance*, IsWholeSong*);
  virtual ~Menus();

  virtual StringArray getMenuBarNames();
  virtual PopupMenu getMenuForIndex(int menuIndex, const String& name);
  virtual void menuItemSelected(int, int) {}

  virtual void operator()(None) {
    menuItemsChanged();
  }

  virtual void operator()(const GuiSettings&);

 private:
  MenuMaker* getMenuMaker();

  CriticalSection lock_;
  bool advanced_;
  ptr<IsWholeSong> isWholeSong_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Menus);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_MENUS__
