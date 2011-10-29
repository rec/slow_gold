#include "rec/slow/Components.h"

namespace rec {
namespace slow {

Components::Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      loops_(manager_),
      songData_(manager_),
      directoryTree_(manager_),
      playbackController_(this, data::editable<AppLayout>()),
      mainPage_(this, data::editable<AppLayout>()) {
  waveform_.setManager(manager_);
}


void Components::setActive(bool a) {
  playbackController_.setActive(a);
  mainPage_.setActive(a);
  // mainPage_.resized();
  // setter->applyLater(NULL);
}


}  // namespace slow
}  // namespace rec
