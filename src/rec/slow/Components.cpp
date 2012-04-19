#include "rec/slow/Components.h"

#include "rec/gui/DropTarget.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

static void enableAllDrawableButtons(Component *c, bool enabled) {
  if (DrawableButton* b = dynamic_cast<DrawableButton*>(c)) {
    b->setEnabled(enabled);
    b->buttonStateChanged();
  } else {
    for (int i = 0; i < c->getNumChildComponents(); ++i)
      enableAllDrawableButtons(c->getChildComponent(i), enabled);
  }
}

Components::Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      timeController_(new gui::audio::TimeController),
      loops_(new gui::audio::Loops()),
      songData_(new gui::SongData(instance->menus_.get())),
      transformController_(new gui::audio::TransformController),
      transportController_(
          new gui::audio::TransportController(timeController_.get())),
      directoryTree_(new widget::tree::Root(instance->menus_.get())),
      waveform_(new gui::DropTarget<widget::waveform::Waveform>()),
      modeSelector_(new gui::audio::ModeSelector()),
	  commandBar_(new gui::audio::CommandBar) {
  loops_->setModel(loops_.get());
  mainPage_.reset(new MainPage(this));
  setDefaultCuttable(loops_.get());
}

Components::~Components() {}

void Components::init() {
  directoryTree_->init();
  timeController_->init();
  loops_->init();
  songData_->init();
  transformController_->init();
  transportController_->init();
  waveform_->init();
  modeSelector_->init();
  mainPage_->init();
}

void Components::setEnabled(bool enabled) {
  thread::callAsync(this, &Components::doSetEnabled, enabled);
}

void Components::doSetEnabled(bool enabled) {
  timeController_->setEnabled(enabled);
  loops_->setEnabled(enabled);
  songData_->setEnabled(enabled);
  transformController_->setEnabled(enabled);
  transportController_->setEnabled(enabled);
  waveform_->setEnabled(enabled);
  modeSelector_->setEnabled(enabled);
  commandBar_->setEnabled(enabled);
  mainPage_->setEnabled(enabled);

  enableAllDrawableButtons(transportController_.get(), enabled);
  enableAllDrawableButtons(modeSelector_.get(), enabled);
  enableAllDrawableButtons(commandBar_.get(), enabled);
}

}  // namespace slow
}  // namespace rec
