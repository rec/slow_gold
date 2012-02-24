#include <google/protobuf/descriptor.h>

#include "rec/slow/MainPage.h"

#include "rec/base/ArraySize.h"
#include "rec/data/Address.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

using namespace juce;

namespace rec {
namespace slow {

using namespace rec::widget::waveform;
using data::Address;

namespace {

const int MIN_NAV_PANEL = 100;
const double MIN_RESIZER = 7.0;
const int MIN_WAVEFORM = 150;
const int MIN_PLAYBACK_PANEL = 100;
const int MIN_HELP_PANEL = 200;
const int MIN_TRANSFORM_PANEL = 250;
const int MIN_TRANSPORT_PANEL = 340;
const int MIN_SONG_DATA = 150;
const int MIN_LOOPS = 250;
const int MIN_DIRECTORY = 75;
const int HELP_CAPTION_HEIGHT = 28;

template <typename Type>
void add(gui::Layout* layout, Type* t, double min, double max, double pref) {
  layout->addToLayout(t, min, max, pref);
}

template <typename Type>
void add(gui::Layout* layout, ptr<Type> &t, double min, double max, double p) {
  layout->addToLayout(t.get(), min, max, p);
}

template <typename Type>
void add(gui::Layout* layout, Type t, double size) {
  add(layout, t, size, size, size);
}

static const string& layoutTypeName() {
  static string name = getTypeName<AppLayout>();
  return name;
}

class MainPanel : public gui::Layout {
 public:
  MainPanel() : gui::Layout("Main", VERTICAL) {}

#if JUCE_WINDOWS
  virtual void paintOverChildren(Graphics& g) {
    g.setColour(juce::Colours::black);
    g.drawLine(0.0f, 0.0f, static_cast<float>(getWidth()), 0);
  }
#endif
};

}  // namespace

MainPage::MainPage(Components* components)
    : mainPanel_(new MainPanel),
      navigationPanel_("Navigation"),
      playbackPanel_("Playback"),
      helpPanel_("Help", VERTICAL),
      transformPanel_("Transform"),
      controlPanel_("Control"),

      navigationResizer_(layoutTypeName(), "navigation_y", mainPanel_.get(), 1),

      directoryResizer_(layoutTypeName(), "directory_x", &navigationPanel_, 1),
      metadataResizer_(layoutTypeName(), "metadata_x", &navigationPanel_, 3),

      helpResizer_(layoutTypeName(), "help_x", &playbackPanel_, 1),
      transformResizer_(layoutTypeName(), "transform_x", &playbackPanel_, 3),
      helpCaption_("", ""),
      helpBody_("", "") {
  add(mainPanel_.get(), &navigationPanel_, MIN_NAV_PANEL, -1.0, -0.4);
  add(mainPanel_.get(), &navigationResizer_, MIN_RESIZER);

  Component* waveform = components->waveform_.get();

  add(mainPanel_.get(), waveform, MIN_WAVEFORM, -1.0, -0.5);
  waveform->addAndMakeVisible(components->modeSelector_.get());
  waveform->addAndMakeVisible(components->commandBar_.get());

  add(mainPanel_.get(), &playbackPanel_, MIN_PLAYBACK_PANEL);

  // Navigation panel.
  components->directoryTree_->treeView()->setTooltip(
      "CD Window:  Any CDs that you have in "
      "your computer's CD drives will appear here.");
  add(&navigationPanel_, components->directoryTree_->treeView(), MIN_DIRECTORY, -1.0, -0.2);
  add(&navigationPanel_, &directoryResizer_, MIN_RESIZER);
  add(&navigationPanel_, components->songData_, MIN_SONG_DATA, -1.0, -0.30);
  add(&navigationPanel_, &metadataResizer_, MIN_RESIZER);
  add(&navigationPanel_, components->loops_.get(), MIN_LOOPS, -1.0, -0.3);

  // Playback panel.
  String helpHelp = "Help Panel: Shows help about whatever the mouse is over.";
  helpPanel_.setTooltip(helpHelp);

  helpCaption_.setTooltip(helpHelp);
  helpCaption_.setColour(juce::Label::textColourId, juce::Colours::darkgreen);
  helpCaption_.setJustificationType(Justification::centred);
  Font font = helpCaption_.getFont();
  font.setBold(true);
  font.setHeight(font.getHeight() + 2);
  helpBody_.setFont(font);
  font.setHeight(font.getHeight() + 3);
  helpCaption_.setFont(font);

  helpBody_.setTooltip(helpHelp);
  helpBody_.setColour(juce::Label::textColourId, juce::Colours::darkgreen);
  helpBody_.setJustificationType(Justification::topLeft);

  add(&playbackPanel_, &helpPanel_, MIN_HELP_PANEL, -1.0, -0.20);
  add(&helpPanel_, &helpCaption_, HELP_CAPTION_HEIGHT);
  add(&helpPanel_, &helpBody_, -0.1, -1.0, -0.7);

  add(&playbackPanel_, &helpResizer_, 5.0);
  add(&playbackPanel_, components->transformController_, MIN_TRANSFORM_PANEL, -1.0, -0.75);
  add(&playbackPanel_, &transformResizer_, 5.0);
  add(&playbackPanel_, components->transportController_.get(), MIN_TRANSPORT_PANEL, -1.0, -0.40);
}

MainPage::~MainPage() {}

void MainPage::startListening() {
  navigationResizer_.startListening();
  directoryResizer_.startListening();
  metadataResizer_.startListening();
  helpResizer_.startListening();
  transformResizer_.startListening();
}

void MainPage::setTooltip(const String& tt) {
  String caption, body = tt;
  int pos = tt.indexOf(":");
  if (pos != -1) {
    caption = tt.substring(0, pos).trim();
    body = tt.substring(pos + 1).trim();
  }
  helpCaption_.setText(caption, false);
  helpBody_.setText(body, false);
}

void MainPage::setEnabled(bool enabled) {
  mainPanel_->setEnabled(enabled);
  navigationPanel_.setEnabled(enabled);
  playbackPanel_.setEnabled(enabled);
  transformPanel_.setEnabled(enabled);
  controlPanel_.setEnabled(enabled);
}

}  // namespace slow
}  // Namespace rec
