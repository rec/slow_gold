#include "rec/audio/source/DoubleStretchy.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/file/VirtualFile.h"

using rec::audio::stretch::StretchLoop;

namespace rec {
namespace audio {
namespace source {

DoubleStretchy::DoubleStretchy(const VirtualFile& file, const RunnyProto& desc)
    : DoubleRunny(desc), file_(file), ratio_(1.0), offset_(0.0) {
}

DoubleStretchy::~DoubleStretchy() {}

void DoubleStretchy::setLoopPosition(const StretchLoop& loop) {
  ScopedLock l(lock_);
  const Stretch& stretch = loop.stretch();
  ratio_ *= (timeScale(stretch) / stretch::timeScale(stretch));
  loop_ = loop;
}

void DoubleStretchy::prepareRunnyToPlay(Runny* runny) {
  runny->setNextReadPosition(getNextReadPosition());
  ratio_ = 1.0;
  offset_ = 0.0;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
