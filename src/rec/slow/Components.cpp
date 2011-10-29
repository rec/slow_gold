#include "rec/slow/Components.h"

#include "rec/gui/DropTarget.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/PlayerController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/PlaybackController.h"
#include "rec/slow/Target.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

Components::Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      timeController_(new gui::audio::TimeController),
      loops_(new gui::audio::Loops(manager_)),
      songData_(new gui::SongData(manager_)),
      playerController_(new gui::audio::PlayerController),
      transportController_(new gui::audio::TransportController),
      directoryTree_(new widget::tree::Root(manager_)),
      waveform_(new gui::DropTarget<Waveform>()),
      playbackController_(new PlaybackController(this,
                                                 data::editable<AppLayout>())),
      mainPage_(new MainPage(this, data::editable<AppLayout>())) {
  waveform_->setManager(manager_);
}

Components::~Components() {}

void Components::setActive(bool a) {
  playbackController_->setActive(a);
  mainPage_->setActive(a);
  // mainPage_.resized();
  // setter->applyLater(NULL);
}

}  // namespace slow
}  // namespace rec
