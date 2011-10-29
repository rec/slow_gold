#include "rec/slow/Components.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/PlayerController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransportController.h"

namespace rec {
namespace slow {

Components::Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      timeController_(new gui::audio::TimeController),
      loops_(new gui::audio::Loops(manager_)),
      songData_(new gui::SongData(manager_)),
      playerController_(new gui::audio::PlayerController),
      transportController_(new gui::audio::TransportController),
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
