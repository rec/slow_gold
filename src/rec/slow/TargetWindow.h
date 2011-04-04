#ifndef __REC_SLOW_TARGETWINDOW__
#define __REC_SLOW_TARGETWINDOW__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class ComponentContainer;

class TargetWindow : public DocumentWindow {
 public:
	TargetWindow(const String& name,
					const Colour& backgroundColour,
					int requiredButtons,
					bool addToDesktop = true) : DocumentWindow(name, backgroundColour, requiredButtons, addToDesktop) {}
  virtual ComponentContainer* getTarget() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(TargetWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_TARGETWINDOW__
