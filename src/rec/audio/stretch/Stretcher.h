#ifndef __REC_STRETCHER_STRETCHER__
#define __REC_STRETCHER_STRETCHER__

#include "rec/base/scoped_ptr.h"
#include "rec/util/Circular.h"
#include "juce_amalgamated.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace timescaler {

class CircularBuffer;
class Description;

class Stretcher {
 public:
  Stretcher();
  ~Stretcher();

  void startStretch(const Description& description,
                    const AudioSampleBuffer& inbuf, int inStart);

  bool readNextChunk();

  const rec::util::Circular& in() const;
  const rec::util::Circular& out() const;

  AudioSampleBuffer* getBuffer() { return buffer_.get(); }
  AudioSampleBuffer* transferBuffer() { return buffer_.transfer(); }


  static AudioSampleBuffer* stretchOnce(const Description& description,
                                        const AudioSampleBuffer& inbuf);

 private:
  int64 chunkSize_;
  scoped_ptr<AudioSampleBuffer> buffer_;
  scoped_ptr<CircularBuffer> in_, out_;
  scoped_ptr<AudioTimeScaler> scaler_;
};

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHER_STRETCHER__
