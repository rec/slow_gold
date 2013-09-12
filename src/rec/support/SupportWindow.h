#ifndef __REC_SUPPORT_SUPPORTWINDOW__
#define __REC_SUPPORT_SUPPORTWINDOW__

#include "rec/app/Window.h"

namespace rec {
namespace slow {

class SupportWindow : public app::Window  {
 public:
  explicit SupportWindow(app::GenericApplication*);
  virtual ~SupportWindow() {}

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
  virtual Component* getMainComponent() { return nullptr; }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SupportWindow);
};

}  // namespace slow

namespace support {

void initialize(app::GenericApplication*);
void shutdown(app::GenericApplication*);

}  // namespace support

}  // namespace rec

#endif  // __REC_SUPPORT_SUPPORTWINDOW__
