#include <gflags/gflags.h>

#include "rec/audio/util/AudioFormatManager.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/source/Stretchy.h"

DEFINE_string(stereo, "stereo", "Select from: stereo, mono, left, right, flip, "
              "elim, elim-mono");

DEFINE_double(time_percent, 100.0, "Percent to speed up or slow down time");
DEFINE_int32(semitone_shift, 0, "Semitones to shift the result");
DEFINE_int32(cents_shift, 0, "cents to shift the result");

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::stretch;

static const String ROOT = "/Users/tom/Documents/development/sound-tests"
                           "/results/TakeFive";

StereoProto makeStereo(StereoProto::Type t = StereoProto::PASSTHROUGH,
                       StereoProto::Side s = StereoProto::LEFT_PLUS_RIGHT) {
  StereoProto p;
  p.set_side(s);
  p.set_type(t);
  return p;
}

StereoProto makeStereo(const string& stereo) {
  if (stereo == "stereo")
    return makeStereo();
  else if (stereo == "mono")
    return makeStereo(StereoProto::SINGLE);
  else if (stereo == "left")
    return makeStereo(StereoProto::SINGLE, StereoProto::LEFT);
  else if (stereo == "right")
    return makeStereo(StereoProto::SINGLE, StereoProto::RIGHT);
  else if (stereo == "flip")
    return makeStereo(StereoProto::FLIP);
  else if (stereo == "elim")
    return makeStereo(StereoProto::CENTER_ELIMINATION);
  else if (stereo == "elim-mono")
    return makeStereo(StereoProto::CENTER_ELIMINATION_MONO);
  CHECK(false) << "--stereo was " << stereo;
  return makeStereo();
}

Stretch makeStretch(double timePercent, double semitone, double cents) {
  Stretch s;
  s.set_time_percent(timePercent);
  s.set_semitone_shift(semitone);
  s.set_detune_cents(cents);

  return s;
}

void copyFileOnce(const File& in,
                  int timePercent, int semitone = 0) {
  CHECK(in.exists()) << "File " << str(in) << " doesn't exist";
  ptr<AudioFormatReader> reader(createReader(in));

  String root = in.getFileNameWithoutExtension();
  root += ("-t" + String(timePercent));
  if (semitone > 0)
    root += ("p+" + String(semitone));
  else if (semitone < 0)
    root += ("p" + String(semitone));

  File out = in.getParentDirectory().getChildFile(root + ".wav");

  if (out.exists())
    out.deleteFile();

  AudioFormat* f = getAudioFormatManager()->findFormatForFileExtension(".wav");
  CHECK(f) << "Couldn't find format for extension .wav";

  OutputStream* stream = out.createOutputStream();
  CHECK(stream) << "Couldn't create file " << str(out);
  ptr<AudioFormatWriter> writer(
      f->createWriterFor(stream,
                         reader->sampleRate,
                         reader->numChannels,
                         reader->bitsPerSample,
                         StringPairArray(),
                         0));

  CHECK(writer) << "Couldn't create writer for " << str(out);
  ptr<PositionableAudioSource> src(new AudioFormatReaderSource(reader.get(), false));
  src.reset(new Stereo(src.transfer(), makeStereo(FLAGS_stereo)));

  Stretchy *stretchy = new Stretchy(src.transfer());
  stretchy->setStretch(makeStretch(timePercent, semitone, 0.0));
  stretchy->initialize();
  src.reset(stretchy);
  writer->writeFromAudioSource(*src, src->getTotalLength(), 4096);
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

int main(int argc, char** argv) { return rec::audio::source::main(argc, argv); }
