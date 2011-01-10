#include <google/protobuf/descriptor.h>

#include "rec/slow/app/MainPage.h"

#include "rec/base/ArraySize.h"
#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/app/AppLayout.pb.h"
#include "rec/util/STL.h"
#include "rec/util/file/Util.h"
#include "rec/widget/tree/NodeItem.h"

using namespace juce;

using namespace rec::audio::source;
using namespace rec::proto::arg;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

MainPage::MainPage(AudioDeviceManager* deviceManager)
    : Layout("MainPage"),
      directory_(new Root(NodeDesc())),
      waveform_(WaveformProto()),
      loops_("Loops"),
      openDialogOpen_(false),
      player_(deviceManager) {
  doLayout();

  controller_.timeController()->setTransport(player_.getTransport());
  player_.getTransport()->addListener(waveform_.timeCursor());

  waveform_.addListener(this);
  directory_->addListener(player_.fileListener());
  waveform_.dropBroadcaster()->addListener(player_.fileListener());
  player_.addListener(this);

  directory_->startThread();
  persist::data<VolumeFile>()->requestUpdate();
}

void MainPage::addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo) {
  r->reset(new SetterResizer(Address(addr), lo, lo->size()));
  (*r)->add();
}

void MainPage::doLayout() {
  persist::Data<AppLayout>* data = persist::data<AppLayout>();
  AppLayout a = data->get();

  bool full[] = {a.full_directory(),  a.full_waveform(), a.full_controller()};
  Component* comp[] = {directory_->treeView(), &waveform_, &controller_};
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
    panel_.addToLayout(&loops_);

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
  controller_.setLayoutData();
}

MainPage::~MainPage() {
  controller_.timeController()->setTransport(NULL);
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100;

bool MainPage::keyPressed(const juce::KeyPress& kp) {
  if (kp.getTextCharacter() == ' ') {
    player_.getTransport()->toggle();
    return true;
  }
  return false;
}

void MainPage::doOpen() {
  if (openDialogOpen_)
    return;
  openDialogOpen_ = true;
  juce::FileChooser chooser("Please choose an audio file", File::nonexistent,
                            file::audioFilePatterns(), true);

  if (chooser.browseForFileToOpen())
    (*player_.fileListener())(file::toVolumeFile(chooser.getResult()));

  openDialogOpen_ = false;
}

void MainPage::doClose() {
  (*player_.fileListener())(VolumeFile());
}

void MainPage::operator()(const TimeAndMouseEvent& timeMouse) {
  if (timeMouse.clickCount_ > 1)
    thread::callAsync(this, &MainPage::doOpen);
  else
    player_.setTime(timeMouse.time_);
}

void MainPage::operator()(const VolumeFile& file) {
  controller_.setData(player_.getStretchy());
  controller_(file);
  if (empty(file)) {
    waveform_.setAudioThumbnail(NULL);
  } else {
    waveform_.setAudioThumbnail(player_.cachedThumbnail()->thumbnail());
    player_.cachedThumbnail()->addListener(&waveform_);
    gui::addRecentFile(file);
    controller_.timeController()->setLength(player_.length());
  }
}

void MainPage::clearTime() {
  if (player_.getStretchy())
    player_.getStretchy()->clear();
}

}  // namespace slow
}  // namespace rec
