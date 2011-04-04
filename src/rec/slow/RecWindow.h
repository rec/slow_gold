#ifndef __REC_WINDOW
#define __REC_WINDOW

#include "rec/slow/ComponentContainer.h"
#include "rec/slow/TargetWindow.h"
// #include "rec/data/persist/Persist.h"

using namespace juce;

namespace rec {

#if 0
namespace gui {
class Rectangle;
}
#endif

namespace persist {
template <typename T> class Data;
}

namespace slow {

class AppLayout;

class RecWindow  : public TargetWindow {
 public:
  RecWindow();
  ~RecWindow();

  void closeButtonPressed();
  ComponentContainer* getTarget() { return &container_; }

  virtual void resized();
  virtual void moved();

 private:
  void writeData();

  ApplicationCommandManager commandManager_;
  ComponentContainer container_;
  persist::Data<AppLayout>* data_;

  // TODO: Component* taskbarIcon used to be here.

  DISALLOW_COPY_AND_ASSIGN(RecWindow);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_WINDOW
