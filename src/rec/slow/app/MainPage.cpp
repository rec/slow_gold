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

using namespace juce;

using namespace rec::audio::source;
using namespace rec::proto::arg;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

static const int CHANGE_LOCKER_WAIT = 100;

MainPage::MainPage(AudioDeviceManager& deviceManager)
    : Layout(HORIZONTAL, "MainPage"),
      transportSource_(new AudioTransportSourcePlayer(&deviceManager)),
      panel_(VERTICAL, true, "TreeWaveAndControl"),
      hbar_(Address("directory_height"), panel_.layoutManager(), 1, HORIZONTAL),
      vbar_(Address("loops_width"), layoutManager(), 1, VERTICAL),
      treeRoot_(new Root(NodeDesc())),
      waveform_(WaveformProto()),
      loops_("Loops"),
      controller_(transportSource_.get()),
      stretchy_(NULL),
      timeLocker_(new TimeLocker(CHANGE_LOCKER_WAIT)),
      fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)),
      fileListener_(persist::data<VolumeFile>()),
      openDialogOpen_(false) {
  panel_.addToLayout(treeRoot_->treeView(), 50, -1.0, -0.5);
  panel_.addToLayout(&hbar_, 10, 10, 10);
  panel_.addToLayout(&waveform_, 150, -1.0, -0.5);
  panel_.addToLayout(&controller_, 100, 100, 100);

  addToLayout(&panel_, 200, -1.0, -0.7);
  addToLayout(&vbar_, 10);
  addToLayout(&loops_, 150, 500, -0.3);

  vbar_.setSetter(persist::data<AppLayout>());
  hbar_.setSetter(persist::data<AppLayout>());

  cursor_ = waveform_.addCursor(CursorProto(), 0.0f);

  waveform_.addListener(this);
  treeRoot_->addListener(&fileListener_);
  waveform_.dropBroadcaster()->addListener(&fileListener_);

  treeRoot_->startThread();

  fileLocker_->addListener(this);
  timeLocker_->addListener(this);

  fileLocker_->startThread();
  timeLocker_->startThread();
  persist::data<VolumeFile>()->addListener(fileLocker_.get());
  persist::data<VolumeFile>()->requestUpdate();

  transportSource_->addListener(cursor_);
  transportSource_->update();
}

MainPage::~MainPage() {
  transportSource_->clear();
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100.0f;

void MainPage::operator()(const VolumeFile& file) {
  if (file_ != file) {
    file_ = file;
    controller_.setData(NULL);
    timeLocker_->initialize(0);
    transportSource_->clear();
    cursor_->setTime(0.0f);

    if (empty(file_)) {
      waveform_.setAudioThumbnail(NULL);
      return;
    }

    stretchy_ = persist::data<StretchyProto>(file_);

    thread_ptr<DoubleRunnyBuffer> dr(new DoubleRunnyBuffer(file_, stretchy_));
    if (dr->empty())
      return;

    controller_.setData(stretchy_);

    waveform_.setAudioThumbnail(dr->cachedThumbnail()->thumbnail());
    dr->cachedThumbnail()->addListener(&waveform_);
    doubleRunny_.swap(dr);

    transportSource_->setSource(doubleRunny_.get());
    gui::addRecentFile(file_);
    stretchy_->requestUpdate();
    controller_.setLength(doubleRunny_->getTotalLength() / SAMPLE_RATE);
  }
}

bool MainPage::keyPressed(const juce::KeyPress& kp) {
  if (kp.getTextCharacter() == ' ') {
    transportSource_->toggle();
    return true;
  }
  return false;
}

void MainPage::clearTime() {
  if (stretchy_)
    stretchy_->clear();
}

void MainPage::operator()(const float& time) {
  if (!doubleRunny_ || doubleRunny_->fillFromPosition(SAMPLE_RATE * time))
    transportSource_->setPosition(stretchy_->get().time_scale() * time);

  else
    LOG(ERROR) << "Failed to fill buffer.";
}

void MainPage::doOpen() {
  if (openDialogOpen_)
    return;
  openDialogOpen_ = true;
  juce::FileChooser chooser("Please choose an audio file", File::nonexistent,
                            file::audioFilePatterns(), true);

  if (chooser.browseForFileToOpen())
    fileListener_(file::toVolumeFile(chooser.getResult()));

  openDialogOpen_ = false;
}

void MainPage::doClose() {
  fileListener_(VolumeFile());
}

void MainPage::operator()(const TimeAndMouseEvent& timeMouse) {
  if (timeMouse.clickCount_ > 1)
    thread::callAsync(this, &MainPage::doOpen);
  else
    thread::callAsync(timeLocker_.get(), &TimeLocker::set, timeMouse.time_);
}


}  // namespace slow
}  // namespace rec
