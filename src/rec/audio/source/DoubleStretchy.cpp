#include "rec/audio/source/DoubleStretchy.h"
#include "rec/audio/source/StretchyRunny.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace source {

DoubleStretchy::DoubleStretchy(const VirtualFile& file,
                                         const RunnyProto& desc)
    : DoubleRunny(desc), file_(file), ratio_(1.0), offset_(0.0) {
}

DoubleStretchy::~DoubleStretchy() {}

int64 DoubleStretchy::nextRunnyPosition() const {
  return runny_ ? (runny_->getNextReadPosition() * ratio_) :
      getNextReadPosition();
}

int64 DoubleStretchy::setLoopPosition(const StretchLoop& loop) {
  ScopedLock l(lock_);
  const Stretch& stretch = loop.stretchy();
  ratio_ *= (timeScale(stretch) / stretch::timeScale(stretch));
  loop_ = loop;
  return nextRunnyPosition();
}

void DoubleStretchy::setLoop(const StretchLoop& loop, int pos) {
  ptr<PositionableAudioSource> source(makeSource());
  if (!source) {
    LOG(ERROR) << "Couldn't make source";
    return;
  }

  ptr<Runny> runny(makeStretchyRunny(runnyDesc_, loop.stretchy(),
                                     pos, source.transfer()));
  if (runny)
    setNext(runny.transfer());
}

void DoubleStretchy::prepareToPlay(Runny* runny) {
  runny->setNextReadPosition(nextRunnyPosition());
  ratio_ = 1.0;
  offset_ = 0.0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
