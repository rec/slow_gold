#include <google/protobuf/descriptor.h>

#include "rec/slow/app/MainPage.h"

#include "rec/gui/RecentFiles.h"
#include "rec/widget/waveform/Cursor.h"

using namespace juce;

using namespace rec::audio::source;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

MainPage::MainPage(AudioDeviceManager* deviceManager)
    : Layout("MainPage"),
      player_(deviceManager),
      directory_(new Root(widget::tree::NodeDesc())),
      waveform_(WaveformProto()),
      controller_(player_.getTransport()),
      openDialogOpen_(false) {
  doLayout();

  player_.getTransport()->addListener(waveform_.timeCursor());

  waveform_.addListener(this);
  waveform_.dropBroadcaster()->addListener(player_.fileListener());
  directory_->addListener(player_.fileListener());
  player_.addListener(this);

  directory_->startThread();
  persist::data<VirtualFile>()->requestUpdate();

  player_.getTransport()->addListener(controller_.timeController());
}

void MainPage::addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo) {
  r->reset(new SetterResizer(Address(addr), lo, lo->size()));
  (*r)->add();
}

MainPage::~MainPage() {}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100;

bool MainPage::keyPressed(const juce::KeyPress& kp) {
  switch (kp.getTextCharacter()) {
    case ' ': player_.getTransport()->toggle(); return true;
    case 'x':
    case 'X': addLoopPoint(); return true;
    default: return false;
  }
}

void MainPage::addLoopPoint() {
  if (loops_.getData()) {
    LoopPoint p;
    p.set_time(player_.getTransport()->getCurrentPosition());
    loops_.getData()->append("loop_point", p);
    loops_.getData()->append("selected", false);
  }
}

void MainPage::doOpen() {
  if (openDialogOpen_)
    return;
  openDialogOpen_ = true;
  juce::FileChooser chooser("Please choose an audio file", File::nonexistent,
                            file::audioFilePatterns(), true);

  if (chooser.browseForFileToOpen())
    (*player_.fileListener())(file::toVirtualFile(chooser.getResult()));

  openDialogOpen_ = false;
}

void MainPage::doClose() {
  (*player_.fileListener())(VirtualFile());
}

void MainPage::operator()(const TimeAndMouseEvent& timeMouse) {
  if (timeMouse.clickCount_ > 1)
    thread::callAsync(this, &MainPage::doOpen);
  else
    player_.setTime(timeMouse.time_);
}

void MainPage::operator()(const VirtualFile& file) {
  controller_.setData(player_.getStretchy());
  controller_(file);

  if (empty(file)) {
    waveform_.setAudioThumbnail(NULL);
    loops_.setData(NULL);

  } else {
    loops_.setData(persist::data<LoopPointList>(file));
    if (gui::CachedThumbnail* thumb = player_.cachedThumbnail()) {
      waveform_.setAudioThumbnail(thumb->thumbnail());
      thumb->addListener(&waveform_);
    } else {
      LOG(ERROR) << "Can't get waveform for file " << file.ShortDebugString();
      return;
    }
    gui::addRecentFile(file);

    // Adjust the length of clients - fix this!
    (*(controller_.timeController()))(ClockUpdate(-1, player_.length() / 44100.0));
  }
}

void MainPage::clearTime() {
  if (player_.getStretchy())
    player_.getStretchy()->clear();
}

}  // namespace slow
}  // namespace rec
