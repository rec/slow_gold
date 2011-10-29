#include <google/protobuf/descriptor.h>

#include "rec/slow/MainPage.h"

#include "rec/base/ArraySize.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/audio/Loops.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Slow.h"
#include "rec/slow/PlaybackController.h"
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

MainPage::MainPage(Components* comp, data::Editable* e)
    : Layout("MainPage", HORIZONTAL),
      panel_("MainPagePanel", VERTICAL),
      directoryResizer_("directory_y", &panel_, 1, e),
      waveformResizer_("waveform_y", &panel_, 3, e),
      loopResizer_("loops_x", this, 1, e) {
  doLayout(comp);
}

MainPage::~MainPage() {}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::doLayout(Components* components) {
  panel_.addToLayout(components->directoryTree_->treeView());
  directoryResizer_.add();
  panel_.addToLayout(components->waveform_.get());
  waveformResizer_.add();
  panel_.addToLayout(components->playbackController_.get());

  addToLayout(&panel_);
  loopResizer_.add();
  addToLayout(components->loops_.get());
}

void MainPage::setActive(bool a) {
  directoryResizer_.setActive(a);
  waveformResizer_.setActive(a);
  loopResizer_.setActive(a);
}

}  // namespace slow
}  // namespace rec
