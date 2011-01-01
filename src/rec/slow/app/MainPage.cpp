#include <google/protobuf/descriptor.h>

#include "rec/slow/app/MainPage.h"

#include "rec/base/Arraysize.h"
#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/STL.h"
#include "rec/util/file/Util.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace slow {

using rec::gui::Colors;
using rec::widget::status::time::Dial;
using rec::widget::status::time::DialComponent;
using rec::widget::status::time::Text;
using rec::widget::status::time::TextComponent;

using namespace juce;

using namespace rec::audio::source;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;
using namespace rec::proto::arg;

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
    startStopButton_(String::empty),
    treeRoot_(new Root(NodeDesc())),
    timeScaleSlider_("Time Scale", Address("time_scale")),
    pitchScaleSlider_("Pitch Scale", Address("semitone_shift")),
    fineScaleSlider_("Fine Scale", Address("detune_cents")),
    songTime_(Text()),
    songDial_(realTimeDial()),
    stretchy_(NULL),
    timeLocker_(new TimeLocker(CHANGE_LOCKER_WAIT)),
    fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)),
    fileListener_(persist::data<VolumeFile>()),
    openDialogOpen_(false) {
  setSize(600, 400);

  startStopButton_.setButtonText(T("Play/Stop"));
  startStopButton_.setColour(TextButton::buttonColourId, Colour(0xff79ed7f));

  explanation_[0].setText("Drag this to set the slowdown", false);
  explanation_[1].setText("Semitone tune up or down", false);
  explanation_[2].setText("Detune up or down (in cents)", false);

  for (int i = 0; i < arraysize(explanation_); ++i) {
    explanation_[i].setFont(Font(14.0000f, Font::plain));
    explanation_[i].setJustificationType(Justification::bottomRight);
    explanation_[i].setEditable(false, false, false);
    explanation_[i].setColour(TextEditor::textColourId, Colours::black);
    explanation_[i].setColour(TextEditor::backgroundColourId, Colour(0x0));
    addAndMakeVisible(&(explanation_[i]));
  }

  timeScaleSlider_.setTooltip(T("Drag this to set the slowdown."));
  timeScaleSlider_.setRange(1.0, 3.0, 0.05);
  timeScaleSlider_.setSliderStyle(Slider::LinearHorizontal);
  timeScaleSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  timeScaleSlider_.setValue(1.0);

  pitchScaleSlider_.setTooltip(T("Semitone tune up or down."));
  pitchScaleSlider_.setRange(-7.0, 7.0, 0.5);
  pitchScaleSlider_.setSliderStyle(Slider::LinearHorizontal);
  pitchScaleSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  pitchScaleSlider_.setValue(0.0);

  fineScaleSlider_.setTooltip(T("Detune up or down (in cents)."));
  fineScaleSlider_.setRange(-50.0, 50.0, 1.0);
  fineScaleSlider_.setSliderStyle(Slider::LinearHorizontal);
  fineScaleSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  fineScaleSlider_.setValue(1.0);

  addAndMakeVisible(&waveform_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(treeRoot_->treeView());

  addAndMakeVisible(&timeScaleSlider_);
  addAndMakeVisible(&pitchScaleSlider_);
  addAndMakeVisible(&fineScaleSlider_);
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

  addListener(&songDial_);
  addListener(&songTime_);
  addListener(cursor_);

  fileLocker_->startThread();
  timeLocker_->startThread();
  persist::data<VolumeFile>()->addListener(fileLocker_.get());
  persist::data<VolumeFile>()->requestUpdate();

  transportSource_->update();
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::resized() {
  waveform_.setBounds(16, getHeight() - 221, getWidth() - 32, 123);
  startStopButton_.setBounds(16, getHeight() - 66, 120, 32);
  treeRoot_->treeView()->setBounds(16, 8, getWidth() - 32, getHeight() - 245);

  for (int i = 0; i < arraysize(explanation_); ++i)
    explanation_[i].setBounds(255, getHeight() - 90 + (25 * i), 275, 32);

  timeScaleSlider_.setBounds(150, getHeight() - 85, 200, 24);
  pitchScaleSlider_.setBounds(150, getHeight() - 60, 200, 24);
  fineScaleSlider_.setBounds(150, getHeight() - 35, 200, 24);

  songTime_.setBounds(getWidth() - 120, getHeight() - 70, 110, 22);
  songDial_.setBounds(getWidth() - 46, getHeight() - 46, 36, 36);
}

void MainPage::buttonClicked(Button* buttonThatWasClicked) {
  transportSource_->toggle();
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100.0f;

void MainPage::operator()(const VolumeFile& file) {
  if (file_ != file) {
    file_ = file;
    timeScaleSlider_.setData(NULL);
    pitchScaleSlider_.setData(NULL);
    fineScaleSlider_.setData(NULL);
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

    timeScaleSlider_.setData(stretchy_);
    pitchScaleSlider_.setData(stretchy_);
    fineScaleSlider_.setData(stretchy_);

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
  if (empty(file_))
    thread::callAsync(this, &MainPage::doOpen);
  else
    thread::callAsync(timeLocker_.get(), &TimeLocker::set, timeMouse.first);
}

void MainPage::operator()(float time) {
  if (stretchy_)
    broadcast(time / stretchy_->get().time_scale());
}

}  // namespace slow
}  // namespace rec
