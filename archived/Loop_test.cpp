#include <gtest/gtest.h>
#include "rec/audio/source/Loop.h"
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
    float expected = rampWave(test->totalSampleNumber(), 63);
    EXPECT_EQ(sample, expected) << test->totalSampleNumber();
    return sample == expected;
  };
};

}  // namespace

TEST(RecAudio, Loop) {
  int size = 127;
  AudioSampleBuffer buffer(2, size);
  for (int i = 0; i < size; ++i) {
    for (int c = 0; c < 2; ++c)
      *buffer.getSampleData(c, i) = rampWave(i, 63);
  }
  TestHarness tester(40, 15, 15);
  tester.setSource(new Loop(buffer));

  tester.testAudioSource(RampTester());
}

}  // namespace source
}  // namespace audio
}  // namespace rec
