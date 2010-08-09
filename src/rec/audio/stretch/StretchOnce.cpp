#include <vector>

#include "rec/audio/stretch/Stretcher.h"
#include "rec/audio/Buffer.h"

namespace rec {
namespace audio {
namespace timescaler {

AudioSampleBuffer* stretchOnce(const Description& description,
                               const AudioSampleBuffer& inbuf) {
  Stretcher stretcher_(description, inbuf);
  while (stretcher_.readNextChunk(description.chunk_size()));
  return stretcher_.getBuffer();
}

}  // namespace timescaler
}  // namespace audio
}  // namespace rec
