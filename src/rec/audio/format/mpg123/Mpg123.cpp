#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/audio/format/mpg123/Format.h"

using namespace juce;

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

namespace {

class Initializer {
 public:
  Initializer() { initialize(); }

  Error initialize() {
    if (!running_) {
      initError_ = mpg123_init();
      running_ = true;
    }
    return initError_;
  }

  void exit() {
    if (running_) {
      running_ = false;
      if (!initError_)
        mpg123_exit();
    }
  }

  Error initError_;
  bool running_;

  static Initializer& instance() {
    // C guarantees thread-safe construction of this variable, so we're
    // guaranteed that that first mpg123_init() is atomic - but if you turn it
    // off and on, all bets are off!
    static Initializer i;
    return i;
  }
};

}  // namespace

Error initializeOnce() {
  return Initializer::instance().initError_;
}

void exitOnce() {
  Initializer::instance().exit();
}

StringArray getMp3FileExtensions() {
  static const char* const extensions[] = {".mp3", ".mp2", ".mp1", nullptr};
  return StringArray(extensions);
}

juce::Array<int> getSampleRates() {
  const long* rates;
  size_t ratesCount;
  mpg123_rates(&rates, &ratesCount);

  Array<int> r(rates, ratesCount);
  r.add(0);

  return r;
}

juce::Array<int> getBitDepths() {
  static const int depths[] = {8, 16, 32, 64, 0};
  return Array<int>(depths);
}

int getBitsPerSample(int encoding) {
  return
    (encoding & MPG123_ENC_16) ? 16 :
    (encoding & MPG123_ENC_32) ? 32 :
    (encoding & MPG123_ENC_8) ? 8 :
    (encoding & MPG123_ENC_FLOAT_64) ? 64 :
    0;
}

String getTranslatedName() {
  return TRANS("MP3 Audio file");
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
