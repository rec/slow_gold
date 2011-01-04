#include <google/protobuf/descriptor.h>

#include "rec/slow/app/MainPage.h"

#include "rec/base/Arraysize.h"
#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/util/STL.h"
#include "rec/util/file/Util.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/Trash.h"

using rec::gui::Colors;
using rec::widget::status::time::Dial;
using rec::widget::status::time::DialComponent;
using rec::widget::status::time::Text;
using rec::widget::status::time::TextComponent;

using namespace juce;

using namespace rec::audio::source;
using namespace rec::proto::arg;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;


namespace rec {
namespace slow {

namespace {

Dial realTimeDial() {
  Dial dial;
  Colors* colors = dial.mutable_widget()->mutable_colors();
  colors->add_color()->set_argb(Colours::white.getARGB());
  colors->add_color()->set_argb(Colours::green.getARGB());
  colors->add_color()->set_argb(Colours::red.getARGB());

  return dial;
}

static const int CHANGE_LOCKER_WAIT = 100;

}  // namespace

MainPage::MainPage(AudioDeviceManager& deviceManager)
  : transportSource_(new app::AudioTransportSourcePlayer(&deviceManager)),
    waveform_(WaveformProto()),
    startStopButton_("Start stop button", juce::DrawableButton::ImageFitted),
    disableButton_("Disable pitch/time shift", Address("disabled")),
    treeRoot_(new Root(NodeDesc())),
    songTime_(Text()),
    songDial_(realTimeDial()),
    stretchy_(NULL),
    timeLocker_(new TimeLocker(CHANGE_LOCKER_WAIT)),
    fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)),
    fileListener_(persist::data<VolumeFile>()),
    openDialogOpen_(false) {
  setSize(600, 400);

  startStopButton_.setImages(gui::icon::MediaPlaybackStart::get(),
                             NULL, NULL, NULL,
                             gui::icon::MediaPlaybackStop::get());
  startStopButton_.setClickingTogglesState(true);

  addAndMakeVisible(&waveform_);
  addAndMakeVisible(&disableButton_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(treeRoot_->treeView());
  addAndMakeVisible(&stretchyController_);

  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);

  cursor_ = waveform_.addCursor(CursorProto(), 0.0f);

  startStopButton_.addListener(this);
  waveform_.addListener(this);
  treeRoot_->addListener(&fileListener_);
  waveform_.dropBroadcaster()->addListener(&fileListener_);

  treeRoot_->startThread();

  fileLocker_->addListener(this);
  timeLocker_->addListener(this);

  transportSource_->addListener(this);
  transportSource_->changeBroadcaster()->addListener(this);

  disableButton_.addListener(this);

  addListener(&songDial_);
  addListener(&songTime_);
  addListener(cursor_);

  fileLocker_->startThread();
  timeLocker_->startThread();
  persist::data<VolumeFile>()->addListener(fileLocker_.get());
  persist::data<VolumeFile>()->requestUpdate();

  transportSource_->update();
}

MainPage::~MainPage() {
  transportSource_->stop();
  transportSource_->setSource(NULL);
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    transportSource_->toggle();

  else if (button == &disableButton_)
    stretchyController_.setEnabled(!disableButton_.getToggleState());
}

void MainPage::resized() {
  waveform_.setBounds(16, getHeight() - 221, getWidth() - 32, 123);
  startStopButton_.setBounds(16, getHeight() - 90, 42, 42);
  disableButton_.setBounds(16, getHeight() - 36, 150, 20);
  treeRoot_->treeView()->setBounds(16, 8, getWidth() - 32, getHeight() - 245);
  stretchyController_.setBounds(200, getHeight() - 90, getWidth() - 250, 85);

  songTime_.setBounds(getWidth() - 120, getHeight() - 70, 110, 22);
  songDial_.setBounds(getWidth() - 46, getHeight() - 46, 36, 36);
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100.0f;

void MainPage::operator()(const VolumeFile& file) {
  if (file_ != file) {
    file_ = file;
    stretchyController_.setData(NULL);
    disableButton_.setData(NULL);
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

    stretchyController_.setData(stretchy_);
    disableButton_.setData(stretchy_);
    thread::callAsync(&stretchyController_, &Component::setEnabled,
                      !stretchy_->get().disabled());

    waveform_.setAudioThumbnail(dr->cachedThumbnail()->thumbnail());
    dr->cachedThumbnail()->addListener(&waveform_);
    doubleRunny_.swap(dr);

    transportSource_->setSource(doubleRunny_.get());
    songDial_.setLength(doubleRunny_->getTotalLength() / SAMPLE_RATE);
    gui::addRecentFile(file_);
    stretchy_->requestUpdate();
  }
}

void MainPage::clearTime() {
  if (stretchy_)
    stretchy_->clear();
}

void MainPage::operator()(const float& time) {
  // DLOG(INFO) << "Callback on time " << time;
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

void MainPage::operator()(float time) {
  if (stretchy_)
    broadcast(time / stretchy_->get().time_scale());
}

void MainPage::setButtonState() {
  startStopButton_.setToggleState(transportSource_->isPlaying(), false);
  startStopButton_.repaint();
}


void MainPage::operator()(const AudioTransportSourcePlayer& player) {
  thread::callAsync(this, &MainPage::setButtonState);
}

}  // namespace slow
}  // namespace rec
