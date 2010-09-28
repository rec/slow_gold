#include <gtest/gtest.h>

#include "rec/audio/source/DoubleStretchy.h"
#include "rec/audio/source/Testy.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/util/TestData.h"

namespace rec {
namespace audio {
namespace source {

using rec::util::testFile;
using rec::audio::timescaler::TimeStretch;

static AudioFormatReaderSource* newSource() {
  AudioFormatManager* afm = AudioFormatManager::getInstance();
  AudioFormatReader* r = afm->createReaderFor(testFile("test1.wav"));
  return new AudioFormatReaderSource(r, true);
}

TEST(RecAudioSource, DoubleStretchyFile) {
  rec::audio::format::mpg123::initializeOnce();
  DoubleStretchy ds(newSource(), newSource());
  ds.setDescription(TimeStretch());
  while (ds.fillNext());
  EXPECT_EQ(ds.available(), 44100);
}

TEST(RecAudioSource, DoubleStretchy) {
  rec::audio::format::mpg123::initializeOnce();

  Testy t1, t2;
  DoubleStretchy ds(new Testy, new Testy);
  ds.setDescription(TimeStretch());
  while (ds.fillNext());
  EXPECT_EQ(ds.available(), 128);

  Testy::expectNear(&ds, 0.0086, 2);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
