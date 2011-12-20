#include "rec/slow/Components.h"

#include "rec/gui/DropTarget.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/TransformController.h"
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
#include "rec/gui/audio/ModeSelector.h"

namespace rec {
namespace slow {

Components::Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      timeController_(new gui::audio::TimeController),
      loops_(new gui::audio::Loops(instance->menus_.get())),
      songData_(new gui::SongData(instance->menus_.get())),
      transformController_(new gui::audio::TransformController),
      transportController_(new gui::audio::TransportController(timeController_.get())),
      directoryTree_(new widget::tree::Root(instance->menus_.get())),
      waveform_(new gui::DropTarget<widget::waveform::Waveform>()),
      modeSelector_(new gui::audio::ModeSelector()),
      commandBar_(new gui::audio::CommandBar),
      mainPage_(new MainPage(this)) {
  setDefaultCuttable(loops_.get());
}

Components::~Components() {}

}  // namespace slow
}  // namespace rec
