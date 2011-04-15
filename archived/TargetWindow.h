#ifndef __REC_SLOW_TARGETWINDOW__
#define __REC_SLOW_TARGETWINDOW__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class TargetWindow : public DocumentWindow {
 public:
	TargetWindow(const String& name,
               const Colour& backgroundColour,
               int requiredButtons = 0,
               bool addToDesktop = true)
      : DocumentWindow(name, backgroundColour, requiredButtons, addToDesktop) {
  }
  virtual MenuBarModel* getMenuBar() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(TargetWindow);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_SLOW_TARGETWINDOW__
