#ifndef __REC_AUDIO_FORMAT_OFFSETAUDIOFORMATREADER__
#define __REC_AUDIO_FORMAT_OFFSETAUDIOFORMATREADER__

#include "rec/base/base.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace audio {
namespace format {

class OffsetAudioFormatReader : public AudioFormatReader {
 public:
  OffsetAudioFormatReader(AudioFormatReader* r, int64 off, int64 length)
      : AudioFormatReader(NULL, r->getFormatName()), reader_(r), offset_(off) {
    sampleRate = r->sampleRate;
    bitsPerSample = r->bitsPerSample;
    lengthInSamples = length;
    numChannels = r->numChannels;
    usesFloatingPointData = r->usesFloatingPointData;
    metadataValues = r->metadataValues;
  }
  
  virtual ~OffsetAudioFormatReader() {}

  virtual bool readSamples (int** destSamples,
                            int numDestChannels,
                            int startOffsetInDestBuffer,
                            int64 startSampleInFile,
                            int numSamples) {
    return reader_->readSamples(destSamples,
                                numDestChannels,
                                startOffsetInDestBuffer,
                                startSampleInFile + offset_,
                                numSamples);
  }

 private:
  scoped_ptr<AudioFormatReader> reader_;
  const int offset_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(OffsetAudioFormatReader);
};

}  // namespace format
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_OFFSETAUDIOFORMATREADER__
