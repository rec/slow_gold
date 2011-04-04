#ifndef __REC_APP_APPLICATION__
#define __REC_APP_APPLICATION__

#include "rec/slow/GenericApplication.h"
#include "rec/slow/TargetWindow.h"

namespace rec {
namespace slow {

template <typename Window>
class Application : public GenericApplication {
 public:
  Application(const String& n, const String& v) : GenericApplication(n, v) {}
  virtual TargetWindow* createWindow() const { return new Window; }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Application);
};

#define REC_APPLICATION_HELPER(NAME, CLASS, BASE_CLASS, VERSION)        \
  struct CLASS : public BASE_CLASS {                                    \
    CLASS() : BASE_CLASS(#NAME, VERSION) {}                             \
  };                                                                    \
  START_JUCE_APPLICATION(CLASS)

#define START_REC_APPLICATION(WINDOW_CLASS, NAME, VERSION)              \
  REC_APPLICATION_HELPER(NAME, NAME ## Application,                     \
                         rec::slow::Application<WINDOW_CLASS>, VERSION)

}  // namespace slow
}  // namespace rec

#endif  // __REC_APP_APPLICATION__
