#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/slow/HasInstance.h"
#include "rec/util/listener/Listener.h"

namespace rec {

namespace gui { class DropFiles; }

namespace slow {

class Instance;
class MouseListener;

class Listeners : // public Listener<const gui::DropFiles&>,
                  public HasInstance {
 public:
  explicit Listeners(Instance* i);
  virtual ~Listeners();

 private:
  ptr<slow::MouseListener> mouseListener_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Listeners);
};

}  // namespace slow1
}  // namespace rec

#endif  // __REC_SLOW_LISTENERS__
