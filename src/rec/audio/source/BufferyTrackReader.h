#ifndef __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__
#define __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

class TrackReader;

class BufferySourceFactory : public Buffery {
 public:
  BufferySourceFactory(const VolumeFile& file, int blockSize);
  ~BufferySourceFactory();

  Source* newSource(int offset = 0);

 private:
  friend class TrackSource;

  typedef std::set<TrackSource*> SourceSet;

  CriticalSection lock_;
  SourceSet sources_;
  bool duringShutdown_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferySourceFactory);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYTRACKREADER__
