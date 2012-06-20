#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

static const int PRELOAD = 10000;  // TODO:  duplicate code.

SampleTime BufferedReader::setReader(AudioFormatReader* reader) {
  Lock l(lock_);
  reset();
  reader_.reset(reader);

  if (!reader_)
    return 0;

  SampleTime size = reader->lengthInSamples;
  if (!setLength(size)) {
    LOG(ERROR) << "Ran out of memory, unable to set frame length";
    reader_.reset();
    return 0;
  }

  return size;
}

bool BufferedReader::coversTime(SampleTime time) const {
  return hasFilled(block::Block(time, time + PRELOAD));
}

}  // namespace util
}  // namespace audio
}  // namespace rec

