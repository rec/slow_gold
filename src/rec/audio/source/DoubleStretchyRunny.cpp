#include "rec/audio/source/DoubleStretchyRunny.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/ShouldExit.h"

namespace rec {
namespace audio {
namespace source {

using stretch::Stretch;
using stretch::StretchLoop;

DoubleStretchyRunny::DoubleStretchyRunny(const VirtualFile& file,
                                         const RunnyProto& desc)
    : DoubleRunny(desc), file_(file), ratio_(1.0), offset_(0.0) {
}

DoubleStretchyRunny::~DoubleStretchyRunny() {}

int64 DoubleStretchyRunny::nextRunnyPosition() const {
  return runny_ ? (runny_->getNextReadPosition() * ratio_) :
      getNextReadPosition();
}

void DoubleStretchyRunny::setLoop(const StretchLoop& loop) {
  const Stretch& desc = loop.stretchy();
  double timeRatio = timeScale(desc);
  int64 position = 0;
  {
    ScopedLock l(lock_);
    ratio_ *= (timeRatio / timeScale(desc));
    loop_ = loop;
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
    setNext(runny.transfer());
  }
}

void DoubleStretchyRunny::prepareToPlay(Runny* runny) {
  runny->setNextReadPosition(nextRunnyPosition());
  ratio_ = 1.0;
  offset_ = 0.0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
