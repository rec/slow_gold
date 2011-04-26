#include "rec/slow/ParameterThread.h"
#include "rec/slow/Threads.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/slow/Instance.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace slow {

using namespace rec::audio::stretch;
using namespace rec::audio::source;

void setVirtualFile(Instance* i, const VirtualFile& f, const StretchLoop& s) {
  ptr<PositionableAudioSource> source(createSourceAndLoadMetadata(f));
  if (!source) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

}

void setStretch(Instance* i, const VirtualFile& f, const StretchLoop& s) {

}

void updateParameters(Instance* i) {
  ParameterUpdater* updater = i->threads_->updater();
  VirtualFile file;
  if (updater->fileLocker_.readAndClearChanged(&file)) {
    StretchLoop loop = persist::get<StretchLoop>(file);
    updater->stretchLocker_.initialize(loop);
    setVirtualFile(i, file, loop);
  } else {
    StretchLoop stretch;
    if (updater->stretchLocker_.readAndClearChanged(&stretch))
      setStretch(i, file, stretch);
  }
}

}  // namespace slow
}  // namespace rec
