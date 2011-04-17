#include <google/protobuf/descriptor.h>

#include "rec/base/ArraySize.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/MainPage.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

using namespace juce;

using namespace rec::audio::source;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

MainPage::MainPage(Instance* instance) //
    : Layout("MainPage"),
      instance_(instance),
  doLayout();
}

void MainPage::addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo) {
  r->reset(new SetterResizer(Address(addr), lo, lo->size()));
  (*r)->add();
}

MainPage::~MainPage() {}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::doLayout() {
  persist::Data<AppLayout>* data = persist::data<AppLayout>();
  AppLayout a = data->get();

  bool full[] = {a.full_directory(),  a.full_waveform(), a.full_controller()};
  Component* comp[] = { instance_->components_.directory_->treeView(),
                        &instance_->components_.waveform_,
                        &instance_->components_.controller_};
  const char* address[] = {"directory_y", "waveform_y", NULL};

  static const int SIZE = arraysize(full);
  DCHECK_EQ(SIZE, arraysize(comp));
  DCHECK_EQ(SIZE, arraysize(address));
  bool vertical = full[0] || full[1] || full[2];
  bool compound = (full[0] + full[1] + full[2]) == 2;
  DCHECK(!compound || full[1]);

  setOrientation(static_cast<Orientation>(vertical));
  panel_.setOrientation(static_cast<Orientation>(!vertical));

  if (!vertical) {
    for (int i = 0; i < SIZE; ++i) {
      panel_.addToLayout(comp[i]);
      if (address[i])
        addResizer(&resizer_[i], address[i], &panel_);
    }
    addToLayout(&panel_);
    addResizer(&loopResizer_, "loops_x", this);
    addToLayout(&loops_);

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
    panel_.addToLayout(&instance_->components_.loops_);

  } else {
    for (int i = 0; i < SIZE; ++i) {
      if (full[i]) {
        addToLayout(comp[i]);
      } else {
        panel_.addToLayout(comp[i]);
        addResizer(&loopResizer_, "loops_x", &panel_);
        panel_.addToLayout(&loops_);
      }
      if (address[i])
        addResizer(&resizer_[i], address[i], this);
    }
  }

  resizer_[0]->setSetter(data);
  resizer_[1]->setSetter(data);
  loopResizer_->setSetter(data);
  // controller_.setLayoutData();  // TODO
}

}  // namespace slow
}  // namespace rec
