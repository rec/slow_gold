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
    : Layout(HORIZONTAL, "MainPage"),
      panel_(VERTICAL, true, "TreeWaveAndControl"),
      hbar_(Address("directory_height"), panel_.layoutManager(), 1, HORIZONTAL),
      vbar_(Address("loops_width"), layoutManager(), 1, VERTICAL),
      treeRoot_(new Root(NodeDesc())),
      waveform_(WaveformProto()),
      loops_("Loops"),
      openDialogOpen_(false),
      player_(deviceManager) {
  controller_.setTransport(player_.getTransport());

  panel_.addToLayout(treeRoot_->treeView(), 50, -1.0, -0.5);
  panel_.addToLayout(&hbar_, 10, 10, 10);
  panel_.addToLayout(&waveform_, 150, -1.0, -0.5);
  panel_.addToLayout(&controller_, 100, 100, 100);

  addToLayout(&panel_, 200, -1.0, -0.7);
  addToLayout(&vbar_, 10);
  addToLayout(&loops_, 150, 500, -0.3);

  vbar_.setSetter(persist::data<AppLayout>());
  hbar_.setSetter(persist::data<AppLayout>());

  player_.getTransport()->addListener(waveform_.timeCursor());

  waveform_.addListener(this);
  treeRoot_->addListener(player_.fileListener());
  waveform_.dropBroadcaster()->addListener(player_.fileListener());
  player_.addListener(this);

  treeRoot_->startThread();
  persist::data<VolumeFile>()->requestUpdate();
}

MainPage::~MainPage() {
  controller_.setTransport(NULL);
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
    // cursor_->setTime(0.0f);  happens automatically?
  } else {
    waveform_.setAudioThumbnail(player_.cachedThumbnail()->thumbnail());
    player_.cachedThumbnail()->addListener(&waveform_);
    gui::addRecentFile(file);
    controller_.setLength(player_.length());
  }
}

void MainPage::clearTime() {
  if (player_.getStretchy())
    player_.getStretchy()->clear();
}

}  // namespace slow
}  // namespace rec
