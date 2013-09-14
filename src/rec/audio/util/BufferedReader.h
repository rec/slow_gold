#ifndef __REC_AUDIO_UTIL_BUFFEREDREADER__
#define __REC_AUDIO_UTIL_BUFFEREDREADER__

#include "rec/audio/Audio.h"
#include "rec/util/range/Fillable.h"

namespace rec {
namespace audio {
namespace util {

class BufferedReader : public Fillable {
 public:
  BufferedReader() {}
  virtual ~BufferedReader() {}

  void setReader(AudioFormatReader* reader);

  virtual Source* makeSource() const = 0;
  virtual bool setLength(int64 length) = 0;
  virtual SampleTime doFillNextBlock(const SampleRange&) = 0;

  bool coversTime(SampleTime time) const;
  AudioFormatReader* reader() { return reader_.get(); }

 protected:
  ptr<AudioFormatReader> reader_;
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_BUFFEREDREADER__
