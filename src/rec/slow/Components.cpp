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
#include "rec/slow/Menus.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

Components::Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      timeController_(new gui::audio::TimeController),
      loops_(new gui::audio::Loops(instance->menus_.get())),
      songData_(new gui::SongData(instance->menus_.get())),
      playerController_(new gui::audio::PlayerController),
      transportController_(new gui::audio::TransportController),
      directoryTree_(new widget::tree::Root(instance->menus_.get())),
      waveform_(new gui::DropTarget<widget::waveform::Waveform>()),
      mainPage_(new MainPage(this, data::editable<AppLayout>())) {
  waveform_->setMenuBarModel(instance->menus_.get());
  setDefaultCuttable(loops_.get());
}

Components::~Components() {}

void Components::setActive(bool a) {
  // TODO: remove!
  mainPage_->setActive(a);
  // mainPage_.resized();
  // setter->applyLater(NULL);
}

}  // namespace slow
}  // namespace rec
