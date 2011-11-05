#include <gflags/gflags.h>

#include "rec/audio/util/AudioFormatManager.h"
#include "rec/audio/util/ProcessAudioFile.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/stretch/Stretchy.h"

DEFINE_string(stereo, "stereo", "Select from: stereo, mono, left, right, flip, "
              "elim, elim-mono");

DEFINE_double(time_percent, 100.0, "Percent to speed up or slow down time");
DEFINE_int32(semitone, 0, "Semitones to shift the result");
DEFINE_int32(cents, -1, "cents to shift the result");

static const juce::File ROOT("/development/sound-tests/results/TakeFive.wav");

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::util;
using namespace rec::audio::stretch;

static Stretch makeStretch() {
  Stretch s;
  s.set_time_percent(FLAGS_time_percent);
  s.set_semitone_shift(FLAGS_semitone);
  s.set_detune_cents(FLAGS_cents);

  return s;
}


void copyFileOnce(const File& in, const File& out) {
  if (out.exists())
    out.deleteFile();

  SourceAndWriter saw = makeSourceAndWriter(in, out);
  Stretchy stretchy(saw.first);
  ptr<AudioFormatWriter> writer(saw.second);

  stretchy.setStretch(makeStretch());
  writer->writeFromAudioSource(stretchy, stretchy.getTotalLength(), 4096);
}

File outFile(const File& f) {
  String out = f.getFileNameWithoutExtension() + "-out" + f.getFileExtension();
  return f.getParentDirectory().getChildFile(out);
}

int main(int argc, char** argv) {
  FLAGS_logtostderr = true;
  google::ParseCommandLineFlags(&argc, &argv, true);
  if (argc == 1)
    copyFileOnce(ROOT, outFile(ROOT));
  else if (argc == 2)
    copyFileOnce(File(argv[1]), outFile(File(argv[1])));
  else
    copyFileOnce(File(argv[1]), File(argv[2]));

  return 0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec

int main(int argc, char** argv) {
  return rec::audio::source::main(argc, argv);
}
