#ifndef __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__
#define __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__

#include "rec/audio/source/Buffery.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace audio {
namespace source {

class BufferySourceFactory : public Buffery {
 public:
  BufferySourceFactory(const widget::tree::VolumeFile& file, int blockSize);
  ~BufferySourceFactory();

  Source* newSource(int offset = 0);
  void removeSource(TrackSource* source);

 protected:
  virtual bool fill(const AudioSourceChannelInfo& info);

 private:


  typedef std::set<TrackSource*> SourceSet;

  const File file_;
  CriticalSection lock_;
  SourceSet sources_;
  AudioThumbnail thumbnail_;
  AudioThumbnailCache thumbnailCache_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferySourceFactory);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__
