#include <google/protobuf/descriptor.h>

#include "rec/slow/Components.h"

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/gui/DropTarget.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/proto/Layout.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/GuiSettings.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/Cuttable.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Zoom.h"

using namespace rec::data;
using namespace rec::program;

namespace rec {
namespace slow {

namespace {

void enableAllDrawableButtons(Component *c, bool enabled) {
  if (DrawableButton* b = dynamic_cast<DrawableButton*>(c)) {
    b->setEnabled(enabled);
    b->buttonStateChanged();
  } else {
    for (int i = 0; i < c->getNumChildComponents(); ++i)
      enableAllDrawableButtons(c->getChildComponent(i), enabled);
  }
}

}  // namespace

Components::Components(Component* parent)
    : mainPanel_(gui::makeLayout("MainPanel", nullptr)),
      parent_(parent) {
}

Components::~Components() {}

void Components::init() {
  auto jm = juceModel();
  treeView_ = jm->getComponent<widget::tree::TreeView>(
      "TreeView", parent_);
  waveform_ = jm->getComponent<widget::waveform::Waveform>(
      "Waveform", parent_);
  waveform_->init();
  gui::audio::Loops* loops = jm->getComponent<gui::audio::Loops>(
      "Loops", parent_);
  loops->setModel(loops);
  setDefaultCuttable(loops);
}

void Components::operator()(const rec::audio::Gain& gain) {
  program::juceModel()->setProperty("muted", gain.mute());
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
  program::juceModel()->setProperty("speed_disabled", not s.time_enabled());
}

widget::tree::Root* Components::directoryTree() {
  return treeView_->root();
}

}  // namespace slow
}  // namespace rec
