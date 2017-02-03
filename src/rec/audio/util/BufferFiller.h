#pragma once

#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace audio {
namespace util {

class BufferedReader;
class CachedThumbnail;

class BufferFiller {
 public:
  BufferFiller();
  virtual ~BufferFiller();

  SampleRange fillOnce();
  bool isFull() const;
  void setReader(const VirtualFile& file, AudioFormatReader* r);
  audio::util::BufferedReader* reader() { return reader_.get(); }
  SampleTime length() const;
  AudioThumbnail* thumbnail();
  void reset();

 private:
  CriticalSection lock_;

  std::unique_ptr<CachedThumbnail> thumbnail_;
  std::unique_ptr<BufferedReader> reader_;
  File file_;

  AudioSampleBuffer updateBuffer_;
  AudioSourceChannelInfo updateInfo_;
  std::unique_ptr<audio::Source> updateSource_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(BufferFiller);
};

}  // namespace util
}  // namespace audio
}  // namespace rec
