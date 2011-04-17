#ifndef __REC_SLOW_WINDOW__
#define __REC_SLOW_WINDOW__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Window : public PersistentWindow {
 public:
  Window() {
    setContentComponent(instance_.components_.mainPage_, true, true);
    setMenuBar(&instance_.menus_);
    setUsingNativeTitleBar(true);
  }

  ~Window() {
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
    // Why isn't this in GenericApplication?
    MenuBarModel::setMacMainMenu(NULL);
#endif
    setMenuBar(NULL);
    setContentComponent(NULL, false);
  }

 private:
  Instance instance_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Window);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_WINDOW__
