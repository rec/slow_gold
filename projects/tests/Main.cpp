
#include <glog/logging.h>
#include <gtest/gtest.h>

#include "rec/app/GenericApplication.h"

namespace rec {
namespace slow {
namespace {

using namespace rec::app;

class TestApplication : public GenericApplication {
 public:
  TestApplication() : GenericApplication(NULL, NULL) {}
  virtual ~TestApplication() {}

  virtual void initialise(const String& commandLine) {
    const char* argv[] = {"test"};
    int argc = 1;
    testing::InitGoogleTest(&argc, (char**) argv);
    setApplicationReturnValue(RUN_ALL_TESTS());
    quit();
  }
  virtual app::Window* createWindow() { return NULL; }

};

}  // namespace
}  // namespace slow
}  // namespace rec

START_JUCE_APPLICATION(rec::slow::TestApplication)
