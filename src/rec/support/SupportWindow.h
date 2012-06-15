#ifndef __REC_SUPPORT_SUPPORTWINDOW__
#define __REC_SUPPORT_SUPPORTWINDOW__

#include "rec/app/Window.h"
#include "rec/slow/HasInstance.h"

namespace rec {
namespace slow {

class SupportWindow : public app::Window, public HasInstance  {
 public:
  explicit SupportWindow(app::GenericApplication*);
  virtual ~SupportWindow();

  virtual void init() {}

  virtual void paint(Graphics& g) {}

  virtual void startup() {}
  virtual void trashPreferences() {}
  virtual void startAboutWindow() {}
  virtual void stopAboutWindow() {}
  virtual void doPostStartup() {}

 protected:
  virtual void doStartup() {}
  virtual void doShutdown() {}

  virtual void constructInstance() {}
  virtual Component* getMainComponent() { return NULL; }
  virtual MenuBarModel* getMenuBarModel() { return NULL; }

 private:
  ptr<Instance> instanceDeleter_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SupportWindow);
};

}  // namespace slow

namespace support {

void initialize(app::GenericApplication*);
void shutdown(app::GenericApplication*);

}  // namespace support

}  // namespace rec

#endif  // __REC_SUPPORT_SUPPORTWINDOW__
