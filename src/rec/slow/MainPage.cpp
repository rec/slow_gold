#include <google/protobuf/descriptor.h>

#include "rec/slow/MainPage.h"

#include "rec/base/ArraySize.h"
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
using gui::SetterResizer;

namespace {

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

}  // namespace

MainPage::MainPage(Components* components, data::Editable* e)
    : mainPanel_("Main", VERTICAL),
      navigationPanel_("Navigation"),
      playbackPanel_("Playback"),
      helpPanel_("Help"),
      transformPanel_("Transform"),
      controlPanel_("Control"),

      navigationResizer_("navigation_y", &mainPanel_, 1, e),
      waveformResizer_("waveform_y", &mainPanel_, 3, e),

      directoryResizer_("directory_x", &navigationPanel_, 1, e),
      metadataResizer_("metadata_x", &navigationPanel_, 3, e),

      helpResizer_("help_x", &playbackPanel_, 1, e),
      transformResizer_("transform_x", &playbackPanel_, 3, e),
      controlResizer_("control_x", &playbackPanel_, 5, e) {
  // Main panel.
  add(&mainPanel_, &navigationPanel_, 150, -1.0, -0.4);
  add(&mainPanel_, &navigationResizer_, 7.0);

  Component* waveform = components->waveform_.get();
  add(&mainPanel_, waveform, 150, -1.0, -0.5);
  waveform->addAndMakeVisible(components->modeSelector_.get());
  waveform->addAndMakeVisible(components->commandBar_.get());

  add(&mainPanel_, &waveformResizer_, 7.0);

  add(&mainPanel_, &playbackPanel_, 150, -1.0, -0.2);

  // Navigation panel.
  add(&navigationPanel_, components->directoryTree_->treeView(), 75, -1.0, -0.2);
  add(&navigationPanel_, &directoryResizer_, 7.0);
  add(&navigationPanel_, components->songData_, 150, -1.0, -0.30);
  add(&navigationPanel_, &metadataResizer_, 7.0);
  add(&navigationPanel_, components->loops_.get(), 250, -1.0, -0.3);

  // Playback panel.
  add(&playbackPanel_, &helpPanel_, 75, -1.0, -0.20);
  add(&playbackPanel_, &helpResizer_, 5.0);
  add(&playbackPanel_, components->transformController_, 180, -1.0, -0.75);
  add(&playbackPanel_, &transformResizer_, 5.0);
  add(&playbackPanel_, components->transportController_.get(), 180, -1.0, -0.40);
}

MainPage::~MainPage() {}

}  // namespace slow
}  // Namespace rec
