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

void DoubleStretchy::setLoop(const StretchLoop& loop) {
  ptr<PositionableAudioSource> source(makeSource());
  if (!source) {
    LOG(ERROR) << "Couldn't make source";
    return;
  }

  const Stretch& stretch = loop.stretchy();
  int64 position = 0;
  {
    ScopedLock l(lock_);
    ratio_ *= (timeScale(stretch) / stretch::timeScale(stretch));
    loop_ = loop;
    position = nextRunnyPosition();
  }

  ptr<Runny> runny(makeStretchyRunny(runnyDesc_, stretch,
                                     position, source.transfer()));
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
