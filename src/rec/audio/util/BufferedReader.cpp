#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

static const int PRELOAD = 10000;

void BufferedReader::setReader(AudioFormatReader* reader) {
  DCHECK(reader);
  Lock l(lock_);
  reset();
  reader_.reset(reader);

  if (reader_) {
    SampleTime size = reader->lengthInSamples;
    if (not setLength(size))
      reader_.reset();
  }

  if (not reader_.get())
    setLength(0);
}

bool BufferedReader::coversTime(SampleTime time) const {
  return hasFilled(SampleRange(time, time + PRELOAD));
}

}  // namespace util
}  // namespace audio
}  // namespace rec

