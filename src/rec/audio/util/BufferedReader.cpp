#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

static const int PRELOAD = 10000;  // TODO:  duplicate code.

Samples<44100> BufferedReader::setReader(AudioFormatReader* reader) {
  Lock l(lock_);
  if (!reader) {
    reader_.reset();
    return 0;
  }

  Samples<44100> size = reader->lengthInSamples;
  if (!setLength(size)) {
    LOG(ERROR) << "Ran out of memory, unable to set frame length";
    return 0;
  }

  setLength(size);
  reader_.reset(reader);
  filled_.clear();
  return size;
}

bool BufferedReader::coversTime(Samples<44100> time) const {
  return hasFilled(block::Block(time, time + PRELOAD));
}

}  // namespace util
}  // namespace audio
}  // namespace rec

