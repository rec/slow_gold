#include "rec/audio/source/DoubleStretchyRunny.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/util/ShouldExit.h"
#include "rec/util/math.h"

namespace rec {
namespace audio {
namespace source {

DoubleStretchyRunny::DoubleStretchyRunny(const VolumeFile& file,
                                         const RunnyProto& desc)
    : DoubleRunny(desc), file_(file), ratio_(1.0) {
}

DoubleStretchyRunny::~DoubleStretchyRunny() {}

int DoubleStretchyRunny::nextRunnyPosition() const {
  return runny_ ? (runny_->getNextReadPosition() * ratio_) :
      getNextReadPosition();
}

void DoubleStretchyRunny::setStretchy(const StretchyProto& desc) {
  DLOG(INFO) << "DoubleStretchyRunny::setStretchy";

  double timeRatio = timeScale(desc);
  int position = 0;
  {
    ScopedLock l(lock_);
    ratio_ *= (timeRatio / timeScale(stretchyDesc_));
#if 0
    LOG(ERROR) << "Scale was " << desc.time_scale()
               << " scale is " << stretchyDesc_.time_scale()
               << " ratio is " << ratio_;
#endif
    stretchyDesc_ = desc;
    position = nextRunnyPosition();
  }

  ptr<PositionableAudioSource> source(makeSource());
  if (!source) {
    LOG(ERROR) << "Couldn't make source";
    return;
  }

  static const double DELTA = 0.00001;
  if (!(desc.passthrough_when_disabled() &&
        near(timeRatio, 1.0, DELTA) &&
        near(pitchScale(desc), 1.0, DELTA))) {
    source.reset(new Stretchy(source.transfer(), desc));
  }

  ptr<Runny> runny(new Runny(source.transfer(), runnyDesc_));
  runny->setNextReadPosition(position);

  Thread* thread = Thread::getCurrentThread();
  while (!(shouldExit(thread) || runny->isFull()))
    runny->fill();

  if (!shouldExit(thread)) {
    runny->startThread();
    set(runny.transfer());
  }
}

void DoubleStretchyRunny::prepareNext(Runny* runny) {
  runny->setNextReadPosition(nextRunnyPosition());
  ratio_ = 1.0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
