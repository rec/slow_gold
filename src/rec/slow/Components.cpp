#include "rec/slow/Components.h"

#include "rec/audio/util/Gain.pb.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/DropTarget.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/proto/Layout.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/Cuttable.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::program;

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

Components::Components()
    : loops_(new gui::audio::Loops()),
      directoryTree_(new widget::tree::Root),
      waveform_(new gui::DropTarget<widget::waveform::Waveform>()) {
  mainPage_.reset(new MainPage(this));
  topComponent_ = mainPage_->panel();
  transportController_ = gui::makeLayout("TransportController", topComponent_);
  transformController_ = gui::makeLayout("TransformController", topComponent_);
  commandBar_ = gui::makeLayout("CommandBar", topComponent_);
  songData_ = gui::makeLayout("SongData", topComponent_);
  modeSelector_ = gui::makeLayout("ModeSelector", topComponent_);

  mainPage_->layoutComponents();
}

Components::~Components() {}

void Components::init() {
  waveform_->init();
  auto jm = juceModel();
  startStopButton_ = jm->getComponent<DrawableButton>("StartStopButton");
  levelSlider_ = jm->getComponent<Component>("LevelSlider");
  speedSlider_ = jm->getComponent<Component>("SpeedSlider");
  gui::audio::Loops* loops = jm->getComponent<gui::audio::Loops>("Loops");
  loops->setModel(loops);
  setDefaultCuttable(loops);
}

void Components::operator()(const rec::audio::Gain& gain) {
 levelSlider_->setEnabled(!gain.mute());
}

void Components::setEnabled(bool enabled) {
  loops_->setEnabled(enabled);
  songData_->setEnabled(enabled);
  transformController_->setEnabled(enabled);
  transportController_->setEnabled(enabled);
  waveform_->setEnabled(enabled);
  modeSelector_->setEnabled(enabled);
  commandBar()->setEnabled(enabled);
  mainPage_->setEnabled(enabled);

  enableAllDrawableButtons(transportController_.get(), enabled);
  enableAllDrawableButtons(modeSelector_.get(), enabled);
  enableAllDrawableButtons(commandBar(), enabled);
}

void Components::operator()(const music::Metadata& md) {
  String name = Trans("(no file loaded)");
  auto currentFile = getInstance()->currentFile_.get();
  if (currentFile && !currentFile->empty()) {
    File file = data::DataListener<music::Metadata>::getData()->getFile();
    name = str(music::getTitle(md, file.getParentDirectory()));
  }

  thread::callAsync(getInstance()->window_, &SlowWindow::setName, name);
}

void Components::operator()(const audio::stretch::Stretch& s) {
  speedSlider_->setEnabled(s.time_enabled());
}

}  // namespace slow
}  // namespace rec
