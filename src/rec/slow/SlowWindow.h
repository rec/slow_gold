#ifndef __REC_SLOW_SLOWWINDOW__
#define __REC_SLOW_SLOWWINDOW__

#include "rec/app/Window.h"
#include "rec/slow/HasInstance.h"

namespace rec {

namespace app { class GenericApplication; }

namespace slow {

class SlowWindow : public app::Window, public HasInstance  {
 public:
  explicit SlowWindow(app::GenericApplication*);
  virtual ~SlowWindow();

  virtual void init();

  virtual void paint(Graphics& g) {
    g.fillAll(juce::Colours::lightgrey);
  }

  virtual void trashPreferences();
  virtual void startAboutWindow();
  virtual void stopAboutWindow();
  virtual void minimisationStateChanged(bool isNowMinimised);
  virtual void doPostStartup();

 protected:
  virtual void doStartup();
  virtual void doShutdown();

  virtual void constructInstance();
  virtual Component* getMainComponent();
  virtual MenuBarModel* getMenuBarModel();
  virtual void activeWindowStatusChanged();

 private:
  ptr<Instance> instanceDeleter_;
  ptr<Component> aboutWindow_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowWindow);
};

void initialize(app::GenericApplication*);
void shutdown(app::GenericApplication*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWWINDOW__
