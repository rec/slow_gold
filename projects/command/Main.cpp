#include <gflags/gflags.h>

#include "rec/audio/util/AudioFormatManager.h"
#include "rec/audio/util/ProcessAudioFile.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/stretch/Stretchy.h"

DEFINE_string(stereo, "stereo", "Select from: stereo, mono, left, right, flip, "
              "elim, elim-mono");

DEFINE_double(time_percent, 100.0, "Percent to speed up or slow down time");
DEFINE_int32(semitone_shift, 0, "Semitones to shift the result");
DEFINE_int32(cents_shift, 0, "cents to shift the result");

static const juce::String ROOT = "/development/sound-tests/results/TakeFive";

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::util;
using namespace rec::audio::stretch;

static Stretch makeStretch(double timePercent, double semitone, double cents) {
  Stretch s;
  s.set_time_percent(timePercent);
  s.set_semitone_shift(semitone);
  s.set_detune_cents(cents);

  return s;
}

void copyFileOnce(const File& in,
                  int timePercent, int semitone = 0) {
  String root = in.getFileNameWithoutExtension();
  root += ("-t" + String(timePercent));
  if (semitone > 0)
    root += ("p+" + String(semitone));
  else if (semitone < 0)
    root += ("p" + String(semitone));

  File out = in.getParentDirectory().getChildFile(root + ".wav");

  if (out.exists())
    out.deleteFile();
  SourceAndWriter saw = makeSourceAndWriter(in, out);
  Stretchy stretchy(saw.first);
  ptr<AudioFormatWriter> writer(saw.second);

  stretchy.setStretch(makeStretch(timePercent, semitone, 0.0));
  writer->writeFromAudioSource(stretchy, stretchy.getTotalLength(), 4096);
}

void copyFile(const File& in, bool time = false) {
  if (time) {
    copyFileOnce(in, 50);
    copyFileOnce(in, 75);
    copyFileOnce(in, 100);
    copyFileOnce(in, 125);
    copyFileOnce(in, 150);
  } else {
    copyFileOnce(in, 100, -5);

#if 0
    copyFileOnce(in, 100, -1);
    copyFileOnce(in, 100, -3);
    copyFileOnce(in, 100, -5);

    copyFileOnce(in, 100, 1);
    copyFileOnce(in, 100, 3);
    copyFileOnce(in, 100, 5);
#endif
  }
}

int main(int argc, char** argv) {
  FLAGS_logtostderr = true;
  google::ParseCommandLineFlags(&argc, &argv, true);
  if (argc == 1)
    copyFile(File(ROOT + ".wav"));
  else
    copyFile(File(argv[1]));

  return 0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec

int main(int argc, char** argv) {
  return rec::audio::source::main(argc, argv);
}
