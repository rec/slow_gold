#include "rec/audio/source/DoubleStretchyRunny.h"
#include "rec/audio/source/StretchyRunny.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace source {

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
  ptr<PositionableAudioSource> source(makeSource());
  if (!source) {
    LOG(ERROR) << "Couldn't make source";
    return;
  }

  const Stretch& stretch = loop.stretchy();
  double timeRatio = timeScale(stretch);
  int64 position = 0;
  {
    ScopedLock l(lock_);
    ratio_ *= (timeRatio / stretch::timeScale(stretch));
    loop_ = loop;
    position = nextRunnyPosition();
  }

  ptr<Runny> runny(makeStretchyRunny(runnyDesc_, stretch, timeRatio,
                                     position, source.transfer()));
  if (runny)
    setNext(runny.transfer());
}

void DoubleStretchyRunny::prepareToPlay(Runny* runny) {
  runny->setNextReadPosition(nextRunnyPosition());
  ratio_ = 1.0;
  offset_ = 0.0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
