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

const int MIN_NAV_PANEL = 100;
const double MIN_RESIZER = 7.0;
const int MIN_WAVEFORM = 150;
const int MIN_PLAYBACK_PANEL = 100;
const int MIN_HELP_PANEL = 200;
const int MIN_TRANSFORM_PANEL = 250;
const double MIN_TRANSPORT_PANEL = 300.0;
const int MIN_SONG_DATA = 150;
const int MIN_LOOPS = 250;
const int MIN_DIRECTORY = 75;
const int HELP_CAPTION_HEIGHT = 28;

template <typename Type>
void add(gui::Panel* layout, Type* t, double min, double max, double pref) {
  layout->addToPanel(t, min, max, pref);
}

template <typename Type>
void add(gui::Panel* layout, ptr<Type> &t, double min, double max, double p) {
  layout->addToPanel(t.get(), min, max, p);
}

template <typename Type>
void add(gui::Panel* layout, Type t, double size) {
  add(layout, t, size, size, size);
}

class MainPanel : public gui::Panel {
 public:
  MainPanel() : gui::Panel("Main", VERTICAL) {}

#if JUCE_WINDOWS
  virtual void paintOverChildren(Graphics& g) {
    g.setColour(juce::Colours::black);
    g.drawLine(0.0f, 0.0f, static_cast<float>(getWidth()), 0);
  }
#endif
};

void enableAllDrawableButtons(Component *c, bool enabled) {
  if (DrawableButton* b = dynamic_cast<DrawableButton*>(c)) {
    b->setEnabled(enabled);
    b->buttonStateChanged();
  } else {
    for (int i = 0; i < c->getNumChildComponents(); ++i)
      enableAllDrawableButtons(c->getChildComponent(i), enabled);
  }
}

const bool USE_NEW_GUI = not true;

}  // namespace

Components::Components()
    : loops_(new gui::audio::Loops()),
      mainPanel_(new MainPanel),
      navigationPanel_(gui::makeLayout("NavigationPanel", mainPanel_.get())),
      playbackPanel_(gui::makeLayout("PlaybackPanel", mainPanel_.get())),

      navigationResizer_(makeAddress<AppLayout>("navigation_y"),
                         mainPanel_.get(), 1),

      waveform_(new gui::DropTarget<widget::waveform::Waveform>()) {
  commandBar_ = gui::makeLayout("CommandBar", mainPanel_.get());
  modeSelector_ = gui::makeLayout("ModeSelector", mainPanel_.get());

  add(mainPanel_.get(), navigationPanel_.get(), MIN_NAV_PANEL, -1.0, -0.2);
  add(mainPanel_.get(), &navigationResizer_, MIN_RESIZER);
  add(mainPanel_.get(), waveform_.get(), MIN_WAVEFORM, -1.0, -0.6);
  waveform_->addAndMakeVisible(modeSelector_.get());
  waveform_->addAndMakeVisible(commandBar_.get());

  add(mainPanel_.get(), playbackPanel_.get(), MIN_PLAYBACK_PANEL);
}

Components::~Components() {}

void Components::init() {
  waveform_->init();
  auto jm = juceModel();
  treeView_ = jm->getComponent<widget::tree::TreeView>("TreeView");
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
  waveform_->setEnabled(enabled);
  modeSelector_->setEnabled(enabled);
  commandBar_->setEnabled(enabled);

  enableAllDrawableButtons(modeSelector_.get(), enabled);
  enableAllDrawableButtons(commandBar_.get(), enabled);
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

widget::tree::Root* Components::directoryTree() {
  return treeView_->root();
}

}  // namespace slow
}  // namespace rec
