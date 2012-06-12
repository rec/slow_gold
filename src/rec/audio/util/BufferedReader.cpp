#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

static const int PRELOAD = 10000;  // TODO:  duplicate code.

SampleTime BufferedReader::setReader(AudioFormatReader* reader) {
  Lock l(lock_);
  reset();

  if (!reader) {
    reader_.reset();
    return 0;
  }

  SampleTime size = reader->lengthInSamples;
  if (!setLength(size)) {
    LOG(ERROR) << "Ran out of memory, unable to set frame length";
    return 0;
  }

  setLength(size);
  reader_.reset(reader);
  DLOG(INFO)
    << " sampleRate: " << reader_->sampleRate
    << " bitsPerSample: " << reader_->bitsPerSample
    << " lengthInSamples: " << reader_->lengthInSamples
    << " numChannels: " << reader_->numChannels
    << " usesFloatingPointData: " << reader_->usesFloatingPointData
    << " metadataValues: " << str(reader_->metadataValues.getDescription());

  return size;
}

bool BufferedReader::coversTime(SampleTime time) const {
  return hasFilled(block::Block(time, time + PRELOAD));
}

}  // namespace util
}  // namespace audio
}  // namespace rec

