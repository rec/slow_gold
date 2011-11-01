#include <google/protobuf/descriptor.h>

#include "rec/slow/MainPage.h"

#include "rec/base/ArraySize.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/PlayerController.h"
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
    : mainPanel_("MainPage", HORIZONTAL),
      nonLoopPanel_("MainPagePanel", VERTICAL),
      playbackPanel_("Main controls"),
      controllerPanel_("Main panel", VERTICAL),
      directoryResizer_("directory_y", &nonLoopPanel_, 1, e),
      waveformResizer_("waveform_y", &nonLoopPanel_, 3, e),
      loopResizer_("loops_x", &mainPanel_, 1, e),
      timeControllerResizer_(Address("clock_x"), &playbackPanel_, 1, e),
      songDataResizer_(Address("songdata_x"), &playbackPanel_, 3, e),
      stretchyResizer_(Address("stretchy_y"), &controllerPanel_, 1, e) {
  add(&mainPanel_, &nonLoopPanel_, 500, -1.0, -0.8);
  add(&mainPanel_, &loopResizer_, 7.0);
  add(&mainPanel_, components->loops_, 80, -1.0, -0.2);

  add(&nonLoopPanel_, components->directoryTree_->treeView(), 75, -1.0, -0.2);
  add(&nonLoopPanel_, &directoryResizer_, 7.0);
  add(&nonLoopPanel_, components->waveform_, 50, -1.0, -0.5);
  add(&nonLoopPanel_, &waveformResizer_, 7.0);
  add(&nonLoopPanel_, &playbackPanel_, 250, -1.0, -0.3);

  add(&playbackPanel_, components->timeController_, 75, -1.0, -0.20);
  add(&playbackPanel_, &timeControllerResizer_, 5.0);
  add(&playbackPanel_, components->songData_, 150, -1.0, -0.30);
  add(&playbackPanel_, &songDataResizer_, 5.0);
  add(&playbackPanel_, &controllerPanel_, 180, -1.0, -0.40);

  add(&controllerPanel_, components->transportController_.get(), 30);
  add(&controllerPanel_, &stretchyResizer_, 5);
  add(&controllerPanel_, components->playerController_, 180, -1.0, -0.75);
}

MainPage::~MainPage() {}

void MainPage::setActive(bool a) {
  directoryResizer_.setActive(a);
  waveformResizer_.setActive(a);
  loopResizer_.setActive(a);
  timeControllerResizer_.setActive(a);
  songDataResizer_.setActive(a);
  stretchyResizer_.setActive(a);
}

}  // namespace slow
}  // namespace rec
