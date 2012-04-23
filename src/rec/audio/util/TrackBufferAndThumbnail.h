#ifndef __REC_AUDIO_UTIL_TRACKBUFFERANDTHUMBNAIL__
#define __REC_AUDIO_UTIL_TRACKBUFFERANDTHUMBNAIL__

#include "rec/audio/util/Frame.h"
#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

class TrackBufferAndThumbnail {
 public:
  TrackBufferAndThumbnail();
  virtual ~TrackBufferAndThumbnail();

  BufferedReader *reader() { return reader_.get(); }
  const BufferedReader& reader() const { return *reader_; }

  Samples<44100> setReader(const VirtualFile& file, AudioFormatReader* r);
  void addBlock(Samples<44100> pos, const AudioSourceChannelInfo& info);

  void writeThumbnail();
  bool cacheWritten() const { return cacheWritten_; }
  juce::AudioThumbnail* thumbnail() { return &thumbnail_; }

 private:
  CriticalSection lock_;

  File file_;
  juce::AudioThumbnailCache cache_;
  bool cacheWritten_;
  juce::AudioThumbnail thumbnail_;

  ptr<BufferedReader> reader_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TrackBufferAndThumbnail);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_TRACKBUFFERANDTHUMBNAIL__
