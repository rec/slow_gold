
#include <glog/logging.h>
#include <gtest/gtest.h>

#include "rec/slow/app/GenericApplication.h"

namespace rec {
namespace slow {
namespace {

class TestApplication : public GenericApplication {
 public:
  TestApplication() : GenericApplication("tests", "1.0") {}
  virtual ~TestApplication() {}

  virtual void initialise(const String& commandLine) {
    GenericApplication::initialise(commandLine);

    const char* argv[] = {"test"};
    int argc = 1;
    testing::InitGoogleTest(&argc, (char**) argv);
    setApplicationReturnValue(RUN_ALL_TESTS());
    quit();
  }
};

}  // namespace
}  // namespace slow
}  // namespace rec

START_JUCE_APPLICATION(rec::slow::TestApplication)
