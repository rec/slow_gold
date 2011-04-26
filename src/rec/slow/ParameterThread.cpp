#include "rec/slow/ParameterThread.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Threads.h"

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
  i->components_->songData_.setFile(f);
}

void setStretch(Instance* i, const VirtualFile& f, const StretchLoop& s) {

}

void updateParameters(Instance* i) {
  ParameterUpdater* updater = i->threads_->updater();
  VirtualFile file;
  if (updater->file()->readAndClearChanged(&file)) {
    StretchLoop loop = persist::get<StretchLoop>(file);
    updater->stretch()->initialize(loop);
    setVirtualFile(i, file, loop);
  } else {
    StretchLoop stretch;
    if (updater->stretch()->readAndClearChanged(&stretch))
      setStretch(i, file, stretch);
  }
}

}  // namespace slow
}  // namespace rec
