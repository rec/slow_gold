#if 0
#include "rec/audio/format/reader/CachedAudioFormatReader.h"

namespace rec {
namespace audio {
namespace format {
namespace reader {

CachedAudioFormatReader::CachedAudioFormatReader(AudioFormatReader* reader)
    : AudioSubsectionReader(reader, 0, reader->lengthInSamples, true) {
  for (int i = 0; i < CHANNELS; ++i)
    cache_[i] = (Sample*) malloc(reader->lengthInSamples * sizeof(Sample));
}

CachedAudioFormatReader::~CachedAudioFormatReader() {
  for (int i = 0; i < CHANNELS; ++i)
    free(cache_(i));
}

bool CachedAudioFormatReader::readSamples(int** destSamples,
                                          int numDestChannels,
                                          int startOffsetInDestBuffer,
                                          int64 startSampleInFile,
                                          int numSamples) {
  Block b(startSampleInFile, startSampleInFile + numSamples);


    bool result = reader->readSamples(destSamples,
                                      numDestChannels,
                                      startOffsetInDestBuffer,
                                      startSampleInFile,
                                      numSamples)

  }

template

virtual bool readSamples(int** destSamples,
                         int numDestChannels,
                         int startOffsetInDestBuffer,
                         int64 startSampleInFile,
                         int numSamples) {
}

}  // namespace reader
}  // namespace format
}  // namespace audio
}  // namespace rec
#endif
