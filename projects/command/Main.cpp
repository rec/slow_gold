#include <gflags/gflags.h>

#include "rec/base/base.h"
#include "rec/audio/util/AudioFormatManager.h"

DEFINE_bool(mono, false, "Add a processor to convert the sound to mono.");
DEFINE_string(input, "/Users/tom/iTunes/The Dave Brubeck Trio/Distinctive Rhythm Instrumentals_ 24 Classic Original Recordings/17 Perfidia.mp3", "file to read");
DEFINE_string(output, "Perfidia.wav", "file to write");


namespace rec {
namespace audio {

int my_main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  DLOG(INFO) << FLAGS_input << ", " << FLAGS_output;
  CHECK(ptr<AudioFormatReader>(createReader(FLAGS_input)));
  return 0;
}

}  // namespace audio
}  // namespace rec

int main(int argc, char** argv) { rec::audio::my_main(argc, argv); }
