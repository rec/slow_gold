#include <gflags/gflags.h>

#include "rec/base/base.h"

DEFINE_bool(mono, false, "Add a processor to convert the sound to mono.");
DEFINE_string(input, "/Users/tom/iTunes/The Dave Brubeck Trio/Distinctive Rhythm Instrumentals_ 24 Classic Original Recordings/17 Perfidia.mp3", "file to read");
DEFINE_string(output, "Perfidia.wav", "file to write");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  DLOG(INFO) << FLAGS_input << ", " << FLAGS_output;
}
