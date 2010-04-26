#include <gtest/gtest.h>
#include "rec/audio/source/Identity.h"
#include "rec/audio/source/Mock.h"
#include "rec/audio/source/TestHarness.h"

namespace rec {
namespace audio {
namespace source {

namespace {

class MockIdentity : public Mock {
 public:
  MockIdentity() {}

 protected:
  virtual float getSample() { return counter_; }

 private:
  DISALLOW_COPY_AND_ASSIGN(MockIdentity);
};

struct RampTester {
  bool operator()(TestHarness* test, float sample) {
    float expected = float(test->totalSampleNumber());
    EXPECT_EQ(expected, sample) << *test;
    return sample == expected;
  };
};

}  // namespace

TEST(RecAudio, Buffered) {
  int sizes[] = { 1, 3, 6, 7 };
  testAudioSource<Identity, MockIdentity, RampTester>(
      sizes, sizes + arraysize(sizes));
}


}  // namespace source
}  // namespace audio
}  // namespace rec
