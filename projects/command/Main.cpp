#include <gflags/gflags.h>

#include "rec/audio/util/AudioFormatManager.h"
#include "rec/audio/util/ProcessAudioFile.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/stretch/Stretchy.h"

DEFINE_string(stereo, "stereo", "Select from: stereo, mono, left, right, flip, "
              "elim, elim-mono");

DEFINE_double(time_percent, 100.0, "Percent to speed up or slow down time");
DEFINE_int32(semitone, 0, "Semitones to shift the result");
DEFINE_int32(cents, 0, "cents to shift the result");

static const juce::String ROOT = "/development/sound-tests/results/TakeFive";

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::util;
using namespace rec::audio::stretch;

static Stretch makeStretch() {
  Stretch s;
  s.set_time_percent(FLAGS_time_percent / 100.0);
  s.set_semitone_shift(FLAGS_semitone);
  s.set_detune_cents(FLAGS_cents);

  return s;
}


void copyFileOnce(const String& inFile, const String& outFile) {
  File in(inFile), out(outFile);
  if (out.exists())
    out.deleteFile();
  SourceAndWriter saw = makeSourceAndWriter(in, out);
  Stretchy stretchy(saw.first);
  ptr<AudioFormatWriter> writer(saw.second);

  stretchy.setStretch(makeStretch());
  writer->writeFromAudioSource(stretchy, stretchy.getTotalLength(), 4096);
}

int main(int argc, char** argv) {
  FLAGS_logtostderr = true;
  google::ParseCommandLineFlags(&argc, &argv, true);
  if (argc == 1)
    copyFileOnce(ROOT + ".wav", "out-" + ROOT + ".wav");
  else if (argc == 2)
    copyFileOnce(argv[1], "out-" + String(argv[1]));
  else
    copyFileOnce(argv[1], argv[2]);

  return 0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec

int main(int argc, char** argv) {
  return rec::audio::source::main(argc, argv);
}
