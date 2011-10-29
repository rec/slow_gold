#include "rec/slow/Components.h"
#include "rec/gui/audio/TimeController.h"

namespace rec {
namespace slow {

Components::Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      timeController_(new gui::audio::TimeController),
      loops_(manager_),
      songData_(manager_),
      directoryTree_(manager_),
      playbackController_(this, data::editable<AppLayout>()),
      mainPage_(this, data::editable<AppLayout>()) {
  waveform_.setManager(manager_);
}

Components::~Components() {}


void Components::setActive(bool a) {
  playbackController_.setActive(a);
  mainPage_.setActive(a);
  // mainPage_.resized();
  // setter->applyLater(NULL);
}


}  // namespace slow
}  // namespace rec
