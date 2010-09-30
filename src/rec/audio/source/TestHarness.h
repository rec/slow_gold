#ifndef __REC_AUDIO_SOURCE_TESTER
#define __REC_AUDIO_SOURCE_TESTER

#include "rec/base/base.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace audio {
namespace source {

struct BufferDescription {
  int channels;
  int bufferCount;
  int priority;
  int samples;
  int wait;
  int waitForShutdown;

  static BufferDescription DEFAULT;
};

class TestHarness {
 public:
  TestHarness(int outputCycles, int outputSamples, int bufferSamples)
      : outputCycles_(outputCycles),
        outputSamples_(outputSamples),
        bufferSamples_(bufferSamples) {
  }

  int totalSampleNumber() const {
    return sampleNumber_ + outputSamples_ * cycle_;
  }

  template <typename Tester>
  bool testAudioSource(Tester tester) {
    for (cycle_ = 0; cycle_ < outputCycles_; ++cycle_) {
      AudioSampleBuffer out(2, outputSamples_);

      AudioSourceChannelInfo info;
      info.startSample = 0;
      info.buffer = &out;
      info.numSamples = outputSamples_;

      wrapper_->getNextAudioBlock(info);
      for (sampleNumber_ = 0; sampleNumber_ < outputSamples_; ++sampleNumber_)
        for (channel_ = 0; channel_ < 2; ++channel_)
          if (!tester(this, *out.getSampleData(channel_, sampleNumber_)))
            return false;
      Thread::sleep(5);  // Allow the computation thread to proceed.
    }
    return true;
  }

  void setSource(AudioSource* source) { wrapper_.reset(source); }

  template <typename Wrapper, typename Source>
  void setWrapper() {
    source_.reset(new Source);
    BufferDescription desc = BufferDescription::DEFAULT;
    desc.samples = bufferSamples_;

    Wrapper* wrapper = new Wrapper(desc);
    wrapper_.reset(wrapper);

    wrapper->setSource(source_.get());
  }

  template <typename Wrapper, typename Source, typename Tester>
  bool test() {
    setWrapper<Wrapper, Source>();
    return testAudioSource(Tester());
  }

  friend std::ostream& operator<< (std::ostream& out,
                                   const TestHarness& test);

 private:
  int outputCycles_;
  int outputSamples_;
  int bufferSamples_;
  int cycle_;
  int channel_;
  int sampleNumber_;
  scoped_ptr<AudioSource> source_;
  scoped_ptr<AudioSource> wrapper_;

  DISALLOW_COPY_AND_ASSIGN(TestHarness);
};

inline std::ostream& operator<< (std::ostream& out,
                                 const TestHarness& test) {
  return
    out << "test: outputCycles_: " << test.outputCycles_
        << ",  outputSamples_: " <<  test.outputSamples_
        << ",  bufferSamples_: " <<  test.bufferSamples_
        << ",  cycle: " <<  test.cycle_
        << ",  channel: " <<  test.channel_
        << ",  sampleNumber_: " <<  test.sampleNumber_
        << std::endl;
}

template <typename Wrapper, typename Source, typename Tester>
static void testAudioSource(int* begin, int* end) {
  for (int* i = begin; i != end; ++i) {
    for (int* j = i; j != end; ++j) {
      TestHarness tester(2 * *j, *i, *j);
      if (!tester.test<Wrapper, Source, Tester>())
        return;
    }
  }
}


}  // namespace source
}  // namespace audio
}  // namespace rec


#endif  // __REC_AUDIO_SOURCE_TESTER
