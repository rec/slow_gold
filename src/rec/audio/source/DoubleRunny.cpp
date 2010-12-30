#include "rec/audio/source/DoubleRunny.h"
#include "rec/util/thread/Trash.h"
#include "rec/audio/source/Clear.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/audio/source/StretchyRunny.h"
#include "rec/util/file/VolumeFile.h"

namespace rec {
namespace audio {
namespace source {

DoubleRunny::DoubleRunny(const VolumeFile& file, const RunnyProto& desc)
    : Wrappy(NULL), file_(file), runnyDesc_(desc) {
}

DoubleRunny::~DoubleRunny() {}

PositionableAudioSource* DoubleRunny::makeSource() {
  ptr<AudioFormatReader> r(createReader(file_));
  return r ? new AudioFormatReaderSource(r.transfer(), true) : NULL;
}

void DoubleRunny::setStretchy(const StretchyProto& desc) {
  DLOG(INFO) << "DoubleRunny::setStretchy";

  int position = 0;
  {
    ScopedLock l(lock_);
    ratio_ *= desc.time_scale() / stretchyDesc_.time_scale();
    stretchyDesc_ = desc;
    if (runny_)
      position = runny_->getNextReadPosition() * ratio_;
  }

  thread_ptr<Runny> runny(makeStretchyRunny(makeSource(), desc,
                                             runnyDesc_, position));
  if (runny) {
    ScopedLock l(lock_);
    nextRunny_.swap(runny);
    if (!runny_) {
      runny_.swap(nextRunny_);
      ratio_ = 1.0;
    }

  } else {
    LOG(ERROR) << "Unable to make source for file " << file_.DebugString();
  }
}

void DoubleRunny::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  thread_ptr<Runny> lastRunny;
  {
    ScopedLock l(lock_);
    if (nextRunny_) {
      nextRunny_->setNextReadPosition(ratio_ * runny_->getNextReadPosition());
      ratio_ = 1.0;
      lastRunny.swap(runny_);
      nextRunny_.swap(runny_);
    }
  }

  if (runny_) {
    runny_->getNextAudioBlock(info);
  } else {
    LOG(ERROR) << "No audio data available";
    clear(info);
  }
}

Source* DoubleRunny::source() const {
  ScopedLock l(lock_);
  return runny_.get();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
