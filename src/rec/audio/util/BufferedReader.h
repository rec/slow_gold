#ifndef __REC_AUDIO_UTIL_BUFFEREDREADER__
#define __REC_AUDIO_UTIL_BUFFEREDREADER__

#include "rec/audio/Audio.h"
#include "rec/util/block/Fillable.h"

namespace rec {
namespace audio {
namespace util {

class BufferedReader : public block::Fillable {
 public:
  BufferedReader() {}
  virtual ~BufferedReader() {}

  Samples<44100> setReader(AudioFormatReader* reader);

  virtual Source* makeSource() const = 0;
  virtual bool setLength(int64 length) = 0;
  virtual block::Size doFillNextBlock(const block::Block& b) = 0;

  bool coversTime(Samples<44100> time) const;

 protected:
  ptr<AudioFormatReader> reader_;
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_BUFFEREDREADER__
