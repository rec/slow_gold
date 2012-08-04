#ifndef __REC_SLOW_ABOUTWINDOW__
#define __REC_SLOW_ABOUTWINDOW__

#include "rec/slow/HasInstance.h"

namespace rec {
namespace slow {

class AboutPane;

class AboutWindow : public Component, public HasInstance {
 public:
  static const int FADE_OUT_TIME = 600;
  explicit AboutWindow(Component* parent, Instance* instance,
                       const String& name, const String& versionNumber);

  virtual void paint(Graphics&) {}

  ~AboutWindow();
  virtual void mouseDown(const MouseEvent&);
  static void registerAllTranslations();

 private:
  Component* parent_;
  ptr<AboutPane> aboutPane_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(AboutWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_ABOUTWINDOW__
