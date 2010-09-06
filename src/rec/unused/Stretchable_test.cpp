#include <gtest/gtest.h>
#include "rec/audio/source/Stretchable.h"
#include "rec/audio/source/Mock.h"
#include "rec/audio/source/TestHarness.h"
#include "rec/audio/Math.h"

using rec::audio::math::rampWave;

namespace rec {
namespace audio {
namespace source {

namespace {

class MockRamp : public Mock {
 public:
  MockRamp(int scale = 100) : scale_(scale) {}

 protected:
  virtual float getSample() {
    return rampWave(counter_, scale_);
  }

 private:
  const int scale_;
  DISALLOW_COPY_AND_ASSIGN(MockRamp);
};

struct RampTester {
  bool operator()(TestHarness* test, float sample) {
    float expected = rampWave(test->totalSampleNumber(), 100);
    EXPECT_NEAR(sample, expected, 0.082) << *test;
    return fabs(sample - expected) < 0.082;
  };
};

}  // namespace

TEST(RecAudio, Stretchable) {
  TestHarness tester(4, 512, 512);
  tester.test<Stretchable, MockRamp, RampTester>();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
