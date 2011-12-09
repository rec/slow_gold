#ifndef __REC_SLOW_SLOWWINDOW__
#define __REC_SLOW_SLOWWINDOW__

#include "rec/app/Window.h"

namespace rec {

namespace app { class GenericApplication; }

namespace slow {

class AppLayout;
class Instance;

class SlowWindow : public app::Window {
 public:
  explicit SlowWindow(app::GenericApplication*);
  virtual ~SlowWindow();
  virtual DefaultRegistry* getDefaultRegistry();
  virtual data::DataRegistry* getDataRegistry();
  virtual void paint(Graphics& g) {
    g.fillAll(juce::Colours::lightgrey);
  }

  virtual void trashPreferences();

 protected:
  virtual void doStartup();
  virtual void constructInstance();
  virtual Component* getMainComponent();
  virtual MenuBarModel* getMenuBarModel();

 private:
  ptr<Instance> instance_;
  ptr<juce::TooltipWindow> tooltipWindow_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWWINDOW__
