#ifndef __REC_SLOW_WINDOW__
#define __REC_SLOW_WINDOW__

#include "rec/gui/PersistentWindow.h"

namespace rec {
namespace slow {

class Instance;

class Window : public gui::PersistentWindow {
 public:
  Window();
  virtual ~Window();

 private:
  ptr<Instance> instance_;
  DISALLOW_COPY_AND_ASSIGN(Window);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_WINDOW__
