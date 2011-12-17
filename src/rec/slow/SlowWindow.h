#ifndef __REC_SLOW_SLOWWINDOW__
#define __REC_SLOW_SLOWWINDOW__

#include "rec/app/Window.h"
#include "rec/slow/HasInstance.h"

namespace rec {

namespace app { class GenericApplication; }

namespace slow {

class AppLayout;
class Instance;

class SlowWindow : public app::Window, public HasInstance {
 public:
  explicit SlowWindow(app::GenericApplication*);
  virtual ~SlowWindow();

  virtual void paint(Graphics& g) {
    g.fillAll(juce::Colours::lightgrey);
  }

  virtual void trashPreferences();
  virtual void registerData(data::MessageRegistrar*);

 protected:
  virtual void doStartup();
  virtual void constructInstance();
  virtual Component* getMainComponent();
  virtual MenuBarModel* getMenuBarModel();
  virtual void activeWindowStatusChanged();

 private:
  ptr<Instance> instanceDeleter_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWWINDOW__
