#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

static const int PRELOAD = 10000;  // TODO:  duplicate code.

SampleTime BufferedReader::setReader(AudioFormatReader* reader) {
  DCHECK(reader);
  Lock l(lock_);
  reset();
  reader_.reset(reader);

  if (!reader_)
    return 0;

  SampleTime size = reader->lengthInSamples;
  if (setLength(size))
    return size;

  reader_.reset();
  return 0;
}

bool BufferedReader::coversTime(SampleTime time) const {
  return hasFilled(block::Block(time, time + PRELOAD));
}

}  // namespace util
}  // namespace audio
}  // namespace rec

