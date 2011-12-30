#ifndef __REC_APP_WINDOW__
#define __REC_APP_WINDOW__

#include "rec/gui/PersistentWindow.h"
#include "rec/util/Listener.h"

namespace rec {
namespace data { class MessageRegistrar; }

namespace app {

class GenericApplication;

// TODO: move this into rec/app
class Window : public gui::PersistentWindow, public Broadcaster<None> {
 public:
  Window(GenericApplication* application,
         const String& name,
         const Colour& bg,
         int requiredButtons,
         bool addToDesktop = true);
  virtual ~Window();

  virtual void initialise();
  virtual void startup();
  virtual void shutdown();
  virtual void focusOfChildComponentChanged(juce::Component::FocusChangeType) {
    broadcast(None());
  }
  virtual void trashPreferences() {}
  GenericApplication* application() { return application_; }
  PopupMenu* getAppleMenu() { return &menu_; }

 protected:
  virtual void constructInstance() = 0;
  virtual Component* getMainComponent() = 0;
  virtual MenuBarModel* getMenuBarModel() = 0;
  virtual void doStartup() = 0;
  virtual void doShutdown() = 0;

 private:
  GenericApplication* application_;
  PopupMenu menu_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Window);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_WINDOW__
