#ifndef __REC_SLOW_SLOWWINDOW__
#define __REC_SLOW_SLOWWINDOW__

#include "rec/app/Window.h"

namespace rec {
namespace slow {

class Instance;

class SlowWindow : public app::Window {
 public:
  SlowWindow();
  virtual ~SlowWindow();
  virtual data::DefaultRegistry* getDefaultRegistry();
  virtual void paint(Graphics& g) {
    g.fillAll(juce::Colours::lightgrey);
  }

 protected:
  virtual void doStartup();
  virtual void constructInstance();
  virtual Component* getMainComponent();
  virtual MenuBarModel* getMenuBarModel();
  virtual void doComputeBounds();

 private:
  ptr<Instance> instance_;

  DISALLOW_COPY_AND_ASSIGN(SlowWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWWINDOW__
