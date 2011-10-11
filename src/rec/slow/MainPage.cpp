#include <google/protobuf/descriptor.h>

#include "rec/base/ArraySize.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/SetterResizer.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Slow.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/MainPage.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

using namespace juce;

// using namespace rec::audio::source;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

MainPage::MainPage(Components* comp) : Layout("MainPage") {
  doLayout(comp);
}

MainPage::~MainPage() {}

void MainPage::addResizer(ptr<gui::SetterResizer>* r, const char* addr, Layout* lo) {
  r->reset(new gui::SetterResizer(data::Address(addr), lo, lo->size()));
  (*r)->add();
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::doLayout(Components* components) {
  persist::TypedEditable<AppLayout>* data = persist::editable<AppLayout>();
  AppLayout a = data->get();

  bool full[] = {a.full_directory(),  a.full_waveform(), a.full_controller()};
  Component* comp[] = { components->directoryTree_.treeView(),
                        &components->waveform_,
                        &components->playbackController_};
  const char* address[] = {"directory_y", "waveform_y", NULL};

  static const uint SIZE = arraysize(full);
  DCHECK_EQ(SIZE, arraysize(comp));
  DCHECK_EQ(SIZE, arraysize(address));
  bool vertical = full[0] || full[1] || full[2];
  bool compound = (full[0] + full[1] + full[2]) == 2;
  DCHECK(!compound || full[1]);

  setOrientation(static_cast<Orientation>(vertical));
  panel_.setOrientation(static_cast<Orientation>(!vertical));

  if (!vertical) {
    for (uint i = 0; i < SIZE; ++i) {
      panel_.addToLayout(comp[i]);
      if (address[i])
        addResizer(&resizer_[i], address[i], &panel_);
    }
    addToLayout(&panel_);
    addResizer(&loopResizer_, "loops_x", this);
    addToLayout(&components->loops_);

  } else if (compound) {
    if (full[0]) {
      addToLayout(comp[0]);
      addResizer(&resizer_[0], address[0], this);

      subpanel_.addToLayout(comp[1]);
      addResizer(&resizer_[1], address[1], &subpanel_);
      subpanel_.addToLayout(comp[2]);

      addToLayout(&panel_);
    } else {
      subpanel_.addToLayout(comp[0]);
      addResizer(&resizer_[0], address[0], &subpanel_);
      subpanel_.addToLayout(comp[1]);
      addResizer(&resizer_[1], address[1], this);

      addToLayout(comp[2]);
    }
    panel_.addToLayout(&subpanel_);
    addResizer(&loopResizer_, "loops_x", &panel_);
    panel_.addToLayout(&components->loops_);

  } else {
    for (uint i = 0; i < SIZE; ++i) {
      if (full[i]) {
        addToLayout(comp[i]);
      } else {
        panel_.addToLayout(comp[i]);
        addResizer(&loopResizer_, "loops_x", &panel_);
        panel_.addToLayout(&components->loops_);
      }
      if (address[i])
        addResizer(&resizer_[i], address[i], this);
    }
  }

  resizer_[0]->setSetter(data);
  resizer_[1]->setSetter(data);
  loopResizer_->setSetter(data);
}

}  // namespace slow
}  // namespace rec
