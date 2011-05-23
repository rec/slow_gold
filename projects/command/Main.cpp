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

static const String ROOT = "/Users/tom/Documents/development/sound-tests/TakeFive";

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

Stretch makeStretch() {
  Stretch s;
  s.set_time_percent(FLAGS_time_percent);
  s.set_semitone_shift(FLAGS_semitone_shift);
  s.set_detune_cents(FLAGS_cents_shift);

  return s;
}

void copyFile(const File& in, const File& out) {
  CHECK(in.exists()) << "File " << str(in) << " doesn't exist";
  ptr<AudioFormatReader> reader(createReader(in));

  if (out.exists())
    out.deleteFile();

  String ext = out.getFileExtension();
  AudioFormat* fmt = getAudioFormatManager()->findFormatForFileExtension(ext);
  CHECK(fmt) << "Couldn't find format for extension " << str(ext);

  ptr<AudioFormatWriter> writer(
      fmt->createWriterFor(out.createOutputStream(),
                           reader->sampleRate,
                           reader->numChannels,
                           reader->bitsPerSample,
                           StringPairArray(),
                           0));

  CHECK(writer) << "Couldn't create writer for " << str(out);
  ptr<PositionableAudioSource> src(new AudioFormatReaderSource(reader.get(), false));
  src.reset(new Stereo(src.transfer(), makeStereo(FLAGS_stereo)));
  
  if (true) {
  Stretchy *stretchy = new Stretchy(src.transfer());
  stretchy->setStretch(makeStretch());
  stretchy->initialize();
  src.reset(stretchy);
  }
  writer->writeFromAudioSource(*src, src->getTotalLength(), 4096);
}

int main(int argc, char** argv) {
  FLAGS_logtostderr = true;
  google::ParseCommandLineFlags(&argc, &argv, true);
  if (argc == 1)
    copyFile(File(ROOT + ".mp3"), File(ROOT + ".out.wav"));
  else if (argc == 2)
    copyFile(File(argv[1]), File(ROOT + ".out.wav"));
  else
    copyFile(File(argv[1]), File(argv[2]));

  return 0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec

int main(int argc, char** argv) { return rec::audio::source::main(argc, argv); }
