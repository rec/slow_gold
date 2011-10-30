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
  mainPanel_.addToLayout(&nonLoopPanel_, 500, -1.0, -0.8);
  mainPanel_.addToLayout(&loopResizer_, 7.0);
  mainPanel_.addToLayout(components->loops_.get(), 80, -1.0, -0.2);

  nonLoopPanel_.addToLayout(components->directoryTree_->treeView(),
                            75, -1.0, -0.2);
  nonLoopPanel_.addToLayout(&directoryResizer_, 7.0);
  nonLoopPanel_.addToLayout(components->waveform_.get(), 50, -1.0, -0.5);
  nonLoopPanel_.addToLayout(&waveformResizer_, 7.0);
  nonLoopPanel_.addToLayout(&playbackPanel_, 300, -1.0, -0.3);

  playbackPanel_.addToLayout(components->timeController_.get(),
                             75, -1.0, -0.20);
  playbackPanel_.addToLayout(&timeControllerResizer_, 5.0);

  playbackPanel_.addToLayout(components->songData_.get(), 150, -1.0, -0.30);
  playbackPanel_.addToLayout(&songDataResizer_, 5.0);

  playbackPanel_.addToLayout(&controllerPanel_, 200, -1.0, -0.40);

  controllerPanel_.addToLayout(components->transportController_.get(), 30);
  controllerPanel_.addToLayout(&stretchyResizer_, 5);
  controllerPanel_.addToLayout(components->playerController_.get(),
                               250, -1.0, -0.75);
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
