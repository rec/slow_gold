#ifndef __REC_SLOW_SLOWWINDOW__
#define __REC_SLOW_SLOWWINDOW__

#include "rec/app/Window.h"

namespace rec {
namespace slow {

class AppLayout;
class Instance;

class SlowWindow : public app::Window, public Listener<const AppLayout&> {
 public:
  SlowWindow();
  virtual ~SlowWindow();
  virtual DefaultRegistry* getDefaultRegistry();
  virtual void paint(Graphics& g) {
    g.fillAll(juce::Colours::lightgrey);
  }

  virtual void operator()(const AppLayout&);
  virtual void trashPreferences();

 protected:
  virtual void doStartup();
  virtual void constructInstance();
  virtual Component* getMainComponent();
  virtual MenuBarModel* getMenuBarModel();
  virtual void doComputeBounds();

 private:
  ptr<Instance> instance_;
  ptr<AppLayout> layout_;

  DISALLOW_COPY_AND_ASSIGN(SlowWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWWINDOW__
