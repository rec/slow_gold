#ifndef __REC_APP_WINDOW__
#define __REC_APP_WINDOW__

#include "rec/gui/PersistentWindow.h"

namespace rec {
namespace app {

// TODO: move this into rec/app
class Window : public gui::PersistentWindow {
 public:
  Window(const String& name,
         const Colour& bg,
         int requiredButtons,
         bool addToDesktop = true);

  virtual void initialise();
  virtual void startup() = 0;
  virtual void shutdown();

  virtual ~Window();

 protected:
  virtual void constructInstance() = 0;
  virtual Component* getMainComponent() = 0;
  virtual MenuBarModel* getMenuBarModel() = 0;
  virtual void doComputeBounds() = 0;

 private:
  bool running_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Window);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_WINDOW__
