#ifndef __REC_APP_APPLICATION__
#define __REC_APP_APPLICATION__

#include "rec/app/GenericApplication.h"

namespace rec {
namespace app {

template <typename WindowImpl>
class Application : public GenericApplication {
 public:
  Application(ApplicationFunction init, ApplicationFunction shutdown)
      : GenericApplication(init, shutdown) {
    google::InitGoogleLogging(str(name()).c_str());
  }
  virtual Window* createWindow() { return new WindowImpl(this); }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Application);
};

// START_REC_APPLICATION(CLASS, NAME, VERSION) wraps START_JUCE_APPLICATION.
//  CLASS must derive from Appliction<SomeWindow>.
//  NAME is the unquoted name of the application.
//  VERSION is the quoted version number.
// example:  START_REC_APPLICATION(SlowWindow, SlowGold, "0.2.23")
//

#define REC_APPLICATION_HELPER(CLASS, BASE, INIT, SHUTDOWN)             \
  struct CLASS : public BASE {                                          \
    CLASS() : BASE(INIT, SHUTDOWN) {}                                   \
  };                                                                    \
  START_JUCE_APPLICATION(CLASS)

#define START_REC_APPLICATION(WINDOW_CLASS, NAME, INIT, SHUTDOWN)       \
  REC_APPLICATION_HELPER(NAME ## Application,                           \
                         rec::app::Application<WINDOW_CLASS>,           \
                         INIT, SHUTDOWN)

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_APPLICATION__
