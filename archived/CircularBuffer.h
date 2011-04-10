#ifndef __REC_AUDIO_SOURCE_CIRCULARBUFFER__
#define __REC_AUDIO_SOURCE_CIRCULARBUFFER__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

class CircularSource : public Range<SampleTime> {
 public:
  CircularBuffer() {}
  virtual ~CircularBuffer() {}

  // SampleTime mod(SampleTime x) const { return util::mod(x, capacity()); }

  SampleTime fullFrom(SampleTime x) const;
  SampleTime emptyFrom(SampleTime x) const;

  void fillFrom(const AudioSourceChannelInfo& info);
  void consumeTo(const AudioSourceChannelInfo& info);

  virtual SampleTime capacity() const = 0;

 private:
  void fill(SampleTime toFill);
  void consume(SampleTime toConsume);

  Range<SampleTime> range_:
  AudioSampleBuffer* buffer_;

  // SampleTime time_;

#if 0
  SampleTime time() const { return time_; }

  void setTime(SampleTime time) { time_ = time; }
#endif


  DISALLOW_COPY_ASSIGN_AND_EMPTY(CircularBuffer);
};


#if 0
, buffer
AudioSampleBuffer
fullFrom
#endif
}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_CIRCULARBUFFER__
