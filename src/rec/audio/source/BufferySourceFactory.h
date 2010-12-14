#ifndef __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__
#define __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__

#include "rec/audio/source/Buffery.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace audio {
namespace source {

class TrackSource;

class BufferySourceFactory {
 public:
  BufferySourceFactory(const widget::tree::VolumeFile& file, int blockSize);
  ~BufferySourceFactory();

  Source* newSource(int offset = 0);
  void removeSource(TrackSource* source);
  CriticalSection& lock() { return lock_; }

 protected:
  virtual bool fill(const Block& block, const AudioSourceChannelInfo& i);

 private:
  typedef std::set<TrackSource*> SourceSet;

  const File file_;
  CriticalSection lock_;
  SourceSet sources_;
  Buffery buffery_;

  AudioThumbnail thumbnail_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferySourceFactory);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__
