#include <google/protobuf/descriptor.h>

#include "rec/slow/MainPage.h"

#include "rec/base/ArraySize.h"
#include "rec/base/DropDead.h"
#include "rec/gui/GetHelpText.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/proto/Layout.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/tree/TreeViewDropAll.h"
#include "rec/widget/waveform/Zoom.h"

using namespace juce;
using namespace rec::data;
using namespace rec::widget::waveform;


TRAN(CD_WINDOW, "CD Window:  Any CDs that you have in "
     "your computer's CD drives will appear here.");

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

}  // namespace

MainPage::MainPage(Components* components)
    : components_(components),
      mainPanel_(new MainPanel),
      navigationPanel_("Navigation"),
      playbackPanel_("Playback"),
      transformPanel_("Transform"),
      controlPanel_("Control"),

      navigationResizer_(makeAddress<AppLayout>("navigation_y"),
                         mainPanel_.get(), 1),

      directoryResizer_(makeAddress<AppLayout>("directory_x"),
                        &navigationPanel_, 1),
      metadataResizer_(makeAddress<AppLayout>("metadata_x"),
                       &navigationPanel_, 3),

      helpResizer_(makeAddress<AppLayout>("help_x"),
                   &playbackPanel_, 1),
      transformResizer_(makeAddress<AppLayout>("transform_x"),
                        &playbackPanel_, 3),
      helpPanel_(gui::makeLayout("HelpPanel", mainPanel_.get())) {
}

void MainPage::layoutComponents() {
  CHECK_DDD(123, 51, int16, int32);
  add(mainPanel_.get(), &navigationPanel_, MIN_NAV_PANEL, -1.0, -0.2);
  add(mainPanel_.get(), &navigationResizer_, MIN_RESIZER);

  Component* waveform = components_->waveform_.get();

  add(mainPanel_.get(), waveform, MIN_WAVEFORM, -1.0, -0.6);
  waveform->addAndMakeVisible(components_->modeSelector_.get());
  waveform->addAndMakeVisible(components_->commandBar_.get());

  add(mainPanel_.get(), &playbackPanel_, MIN_PLAYBACK_PANEL);

  // Navigation panel.
  add(&navigationPanel_, components_->directoryTree_->treeView(), MIN_DIRECTORY, -1.0, -0.2);
  add(&navigationPanel_, &directoryResizer_, MIN_RESIZER);
  add(&navigationPanel_, components_->songData_.get(), MIN_SONG_DATA, -1.0, -0.30);
  add(&navigationPanel_, &metadataResizer_, MIN_RESIZER);
  add(&navigationPanel_, components_->loops_.get(), MIN_LOOPS, -1.0, -0.3);

  add(&playbackPanel_, helpPanel_.get(), MIN_HELP_PANEL, -1.0, -0.20);

  add(&playbackPanel_, &helpResizer_, 5.0);
  add(&playbackPanel_, components_->transformController_.get(),
      MIN_TRANSFORM_PANEL, -1.0, -0.75);
  add(&playbackPanel_, &transformResizer_, 5.0);
  Component *xport = components_->transportController_.get();
  add(&playbackPanel_, xport, MIN_TRANSPORT_PANEL, -1.0, -0.20);
}

void MainPage::languageChanged() {
  components_->directoryTree_->treeView()->setTooltip(t_CD_WINDOW);
}

MainPage::~MainPage() {}

void MainPage::setEnabled(bool enabled) {
  navigationPanel_.setEnabled(enabled);
  playbackPanel_.setEnabled(enabled);
  transformPanel_.setEnabled(enabled);
  controlPanel_.setEnabled(enabled);
}

}  // namespace slow
}  // Namespace rec
