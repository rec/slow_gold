#include "rec/audio/source/DoubleRunny.h"
#include "rec/util/thread/Trash.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/widget/tree/VolumeFile.h"

using namespace rec::util::thread;

namespace rec {
namespace audio {
namespace source {

DoubleRunny::~DoubleRunny() {
  trash::discard(runny_.transfer());
  trash::discard(nextRunny_.transfer());
  trash::empty();
}

PositionableAudioSource* DoubleRunny::makeSource() {
  scoped_ptr<AudioFormatReader> r(createReader(file_));
  return r ? new AudioFormatReaderSource(r.transfer(), true) : NULL;
}

void DoubleRunny::setStretchy(const StretchyProto& desc) {
  // TODO: this should never run on the main thread!
  Thread* thread = Thread::getCurrentThread();
  DLOG(INFO) << "DoubleRunny::setStretchy";

  scoped_ptr<PositionableAudioSource> source(makeSource());
  if (!source) {
    LOG(ERROR) << "Unable to make source for file " << file_.DebugString();
    return;
  }
  scoped_ptr<Stretchy> stretchy(new Stretchy(desc, source.transfer()));
  scoped_ptr<Runny> runny(new Runny(runnyDesc_, stretchy.transfer()));
  {
    ScopedLock l(lock_);
    ratio_ *= desc.time_scale() / stretchyDesc_.time_scale();
    stretchyDesc_ = desc;
    if (runny_)
      runny->setNextReadPosition(runny_->getNextReadPosition() * ratio_);
  }

  while (!runny->fill()) {
    if (thread && thread->threadShouldExit())
      return;
  }
  
  if (thread && thread->threadShouldExit())
    return;

  runny->startThread();

  {
    ScopedLock l(lock_);
    nextRunny_.swap(runny);
    if (!runny_) {
      runny_.swap(nextRunny_);
      ratio_ = 1.0;
    }
  }

  trash::discardAndEmpty(runny.transfer());
}

void DoubleRunny::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  scoped_ptr<Runny> lastRunny;
  {
    ScopedLock l(lock_);
    if (nextRunny_) {
      nextRunny_->setNextReadPosition(ratio_ * runny_->getNextReadPosition());
      ratio_ = 1.0;
      lastRunny.swap(runny_);
      nextRunny_.swap(runny_);
    }
  }

  if (runny_)
    runny_->getNextAudioBlock(info);
  else
    LOG(ERROR) << "No runny";

  trash::discard(lastRunny.transfer());
}

Source* DoubleRunny::source() const {
  ScopedLock l(lock_);
  return runny_.get();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
