#include <gtest/gtest.h>

#include "rec/audio/source/DoubleStretchy.h"
#include "rec/audio/source/Testy.h"
#include "rec/util/TestData.h"

namespace rec {
namespace audio {
namespace source {

using rec::util::testFile;
using rec::audio::timescaler::Description;

static AudioFormatReaderSource* newSource() {
  AudioFormatManager* afm = AudioFormatManager::getInstance();
  AudioFormatReader* r = afm->createReaderFor(testFile("test1.wav"));
  return new AudioFormatReaderSource(r, true);
}

TEST(RecAudioSource, DoubleStretchyFile) {
  scoped_ptr<AudioFormatReaderSource> s1(newSource());
  scoped_ptr<AudioFormatReaderSource> s2(newSource());
  scoped_ptr<AudioFormatReaderSource> s3(newSource());
  DoubleStretchy<AudioFormatReaderSource> ds(Description(), s1.get(), s2.get());
  while (ds.fillNext());
  EXPECT_EQ(ds.available(), 44100);

  // Testy::expectNear(&ds, s3.get(), 0.1, 2);
}

TEST(RecAudioSource, DoubleStretchy) {
  Testy t1, t2;
  DoubleStretchy<Testy> ds(Description(), &t1, &t2);
  while (ds.fillNext());
  EXPECT_EQ(ds.available(), 128);

  Testy::expectNear(&ds, 0.0086, 2);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
