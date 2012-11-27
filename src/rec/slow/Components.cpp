#include "rec/slow/Components.h"

#include "rec/gui/DropTarget.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/Cuttable.h"
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
    : HasInstance(instance),
      manager_(applicationCommandManager()),
      timeController_(new gui::audio::TimeController),
      loops_(new gui::audio::Loops()),
      songData_(new gui::SongData(menus())),
      transformController_(new gui::audio::TransformController),
      transportController_(
          new gui::audio::TransportController(timeController_.get())),
      directoryTree_(new widget::tree::Root(menus())),
      waveform_(new gui::DropTarget<widget::waveform::Waveform>()),
      modeSelector_(new gui::audio::ModeSelector()),
	  commandBar_(new gui::audio::CommandBar) {
  loops_->setModel(loops_.get());
  mainPage_.reset(new MainPage(this));
  setDefaultCuttable(loops_.get());
}

Components::~Components() {}

void Components::init() {
  waveform_->init();
}

void Components::setEnabled(bool enabled) {
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

void Components::operator()(const music::Metadata& md) {
  String name = Trans("(no file loaded)");
  if (currentFile() && !currentFile()->empty()) {
    File file = data::DataListener<music::Metadata>::getData()->getFile();
    name = str(music::getTitle(md, file.getParentDirectory()));
  }

  thread::callAsync(window(), &SlowWindow::setName, name);
}


}  // namespace slow
}  // namespace rec
