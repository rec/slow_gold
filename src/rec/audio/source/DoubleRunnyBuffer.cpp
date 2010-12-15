#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace audio {
namespace source {

DoubleRunnyBuffer::DoubleRunnyBuffer(const VolumeFile& file, int blockSize)
    : buffery_(Snoopy::add(createSource(file), cachedThumbnail_), blockSize) {
}

PositionableAudioSource* DoubleRunnyBuffer::makeSource(const VolumeFile& f) {
  for (int i = 0; !buffery_.hasFilled(READAHEAD); ++i) {
    if (threadShouldExit())
      return NULL;

    if ((i * WAIT_TIME) > MAX_WAIT_TIME) {
      LOG(ERROR) << "Waited for a long time, no data: " << i * WAIT_TIME;
      return NULL;
    }
    wait(WAIT_TIME);
  }

  return threadShouldExit() ? NULL : new BufferySource(buffery_.buffer());
}

virtual void DoubleRunnyBuffer::run() {
  while (!(threadShouldExit() || buffery.isFull()))
    buffery_.fill();
}


}  // namespace source
}  // namespace audio
}  // namespace rec
