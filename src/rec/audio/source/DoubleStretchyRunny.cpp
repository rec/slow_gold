#include "rec/audio/source/DoubleStretchyRunny.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/util/ShouldExit.h"

namespace rec {
namespace audio {
namespace source {

DoubleStretchyRunny::DoubleStretchyRunny(const VolumeFile& file,
                                         const RunnyProto& desc)
    : DoubleRunny(desc), file_(file), ratio_(1.0) {
}

DoubleStretchyRunny::~DoubleStretchyRunny() {}

int DoubleStretchyRunny::nextRunnyPosition() const {
  return runny_ ? (runny_->getNextReadPosition() / ratio_) :
      getNextReadPosition();
}

void DoubleStretchyRunny::setStretchy(const StretchyProto& desc) {
  DLOG(INFO) << "DoubleStretchyRunny::setStretchy";

  int position = 0;
  {
    ScopedLock l(lock_);
    ratio_ *= (desc.time_scale() / stretchyDesc_.time_scale());
    stretchyDesc_ = desc;
    position = nextRunnyPosition();
  }

  if (PositionableAudioSource* source = makeSource()) {
    ptr<Runny> runny(new Runny(new Stretchy(source, desc), runnyDesc_));
    runny->setNextReadPosition(position);

    Thread* thread = Thread::getCurrentThread();
    while (!shouldExit(thread)) {
      if (runny->fill() && !shouldExit(thread)) {
        runny->startThread();
        set(runny.transfer());
        return;
      }
    }
  }
}

void DoubleStretchyRunny::prepareNext(Runny* runny) {
  runny->setNextReadPosition(nextRunnyPosition());
  ratio_ = 1.0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
