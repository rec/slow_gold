#ifndef __REC_AUDIO_FORMAT_READER_CACHEDAUDIOFORMATREADER__
#define __REC_AUDIO_FORMAT_READER_CACHEDAUDIOFORMATREADER__

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace audio {
namespace format {
namespace reader {

typedef int Sample;

class CachedAudioFormatReader : public juce::AudioSubsectionReader {
 public:
  static const int CHANNELS = 2;

  CachedAudioFormatReader(AudioFormatReader* reader);
  virtual ~CachedAudioFormatReader();
  virtual bool readSamples(int** destSamples,
                           int numDestChannels,
                           int startOffsetInDestBuffer,
                           int64 startSampleInFile,
                           int numSamples);

 private:
  CriticalSection lock_;
  BlockSet cachedBlocks_;
  scoped_ptr<AudioFormatReader> reader_;
  Sample *cache_[CHANNELS];

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CachedAudioFormatReader);
};

}  // namespace reader
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_READER_CACHEDAUDIOFORMATREADER__
