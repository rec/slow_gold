#ifndef __REC_AUDIO_UTIL_FILLABLESOURCEREADER__
#define __REC_AUDIO_UTIL_FILLABLESOURCEREADER__

#include "rec/audio/Audio.h"
#include "rec/util/block/Fillable.h"

namespace rec {
namespace audio {
namespace util {

class FillableSourceReader : public block::Fillable {
 public:
  FillableSourceReader() {}
  virtual ~FillableSourceReader() {}

  virtual Source* makeSource() const = 0;
  virtual bool setLength(int64 length) = 0;
  Samples<44100> setReader(AudioFormatReader* reader);

 protected:
  ptr<AudioFormatReader> reader_;
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILLABLESOURCEREADER__
