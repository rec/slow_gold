#include <google/protobuf/descriptor.h>

#include "rec/slow/app/MainPage.h"

#include "rec/gui/RecentFiles.h"
#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace slow {

using rec::gui::Colors;
using rec::widget::status::time::Dial;
using rec::widget::status::time::DialComponent;
using rec::widget::status::time::Text;
using rec::widget::status::time::TextComponent;

using namespace juce;

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
    explanation_(String::empty, T("<Explanation here>.")),
    timeScaleSlider_(Address("time_scale"), T("Time Scale")),
    pitchScaleSlider_(Address("pitch_scale"), T("Pitch Scale")),
    songTime_(Text()),
    songDial_(realTimeDial()),
    stretchy_(NULL),
    fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)),
    fileListener_(getCurrentFileData()->setter()) {
  setSize(600, 400);

  startStopButton_.setButtonText(T("Play/Stop"));
  startStopButton_.setColour(TextButton::buttonColourId, Colour(0xff79ed7f));

  explanation_.setFont(Font(14.0000f, Font::plain));
  explanation_.setJustificationType(Justification::bottomRight);
  explanation_.setEditable(false, false, false);
  explanation_.setColour(TextEditor::textColourId, Colours::black);
  explanation_.setColour(TextEditor::backgroundColourId, Colour(0x0));

  timeScaleSlider_.setTooltip(T("Drag this to set the slowdown."));
  timeScaleSlider_.setRange(0.1, 5, 0);
  timeScaleSlider_.setSliderStyle(Slider::LinearHorizontal);
  timeScaleSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  timeScaleSlider_.setValue(1.0);

  pitchScaleSlider_.setTooltip(T("Drag this to set the pitchscale."));
  pitchScaleSlider_.setRange(0.125, 4, 0);
  pitchScaleSlider_.setSliderStyle(Slider::LinearHorizontal);
  pitchScaleSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  pitchScaleSlider_.setValue(1.0);

  addAndMakeVisible(&waveform_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(treeRoot_->treeView());
  addAndMakeVisible(&explanation_);
  addAndMakeVisible(&timeScaleSlider_);
  addAndMakeVisible(&pitchScaleSlider_);
  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);

  cursor_ = waveform_.addCursor(CursorProto(), 0.0f);

  startStopButton_.addButtonListener(this);
  waveform_.addListener(this);
  treeRoot_->addListener(&fileListener_);

  transportSource_->addListener(&songDial_);
  transportSource_->addListener(&songTime_);
  transportSource_->addListener(cursor_);

  treeRoot_->startThread();

  fileLocker_->addListener(this);
  getCurrentFileData()->addListener(fileLocker_.get());
}

void MainPage::removeFileCallbacks() {
  if (timeLocker_) {
    timeLocker_->removeListener(this);
    trash::discard(&timeLocker_);
  }
}

MainPage::~MainPage() {
  getCurrentFileData()->removeListener(fileLocker_.get());

  startStopButton_.removeButtonListener(this);
  treeRoot_->removeListener(&fileListener_);

  transportSource_->removeListener(&songDial_);
  transportSource_->removeListener(&songTime_);
  transportSource_->removeListener(cursor_);
  getCurrentFileData()->removeListener(fileLocker_.get());

  transportSource_->stop();
  transportSource_->setSource(NULL);

  trash::discard(&treeRoot_);
  trash::discard(&doubleRunny_);
  trash::discard(&transportSource_);
  trash::discard(&fileLocker_);

  removeFileCallbacks();
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::resized() {
  waveform_.setBounds(16, getHeight() - 221, getWidth() - 32, 123);
  startStopButton_.setBounds(16, getHeight() - 46, 150, 32);
  treeRoot_->treeView()->setBounds(16, 8, getWidth() - 32, getHeight() - 245);
  explanation_.setBounds(224, getHeight() - 42, getWidth() - 248, 32);
  timeScaleSlider_.setBounds(300, getHeight() - 90, 200, 24);
  pitchScaleSlider_.setBounds(300, getHeight() - 60, 200, 24);
  songTime_.setBounds(520, getHeight() - 90, 110, 22);
  songDial_.setBounds(640, getHeight() - 90, 36, 36);
}

void MainPage::buttonClicked(Button* buttonThatWasClicked) {
  transportSource_->toggle();
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100.0f;

void MainPage::operator()(const VolumeFile& file) {
  if (file_ != file) {
    removeFileCallbacks();
    file_ = file;
    if (empty(file_))
      return;

    timeLocker_.reset(new TimeLocker(CHANGE_LOCKER_WAIT));
    timeLocker_->set(0);
    timeLocker_->addListener(this);
    timeLocker_->startThread();

    timeScaleSlider_(file_);
    pitchScaleSlider_(file_);

    transportSource_->clear();
    cursor_->setTime(0.0f);
    stretchy_ = persist::getApp()->getData<audio::source::StretchyProto>(file, "timestretch");

    scoped_ptr<DoubleRunnyBuffer> dr(new DoubleRunnyBuffer(file_, stretchy_));
    waveform_.setAudioThumbnail(dr->cachedThumbnail()->thumbnail());
    dr->cachedThumbnail()->addListener(&waveform_);
    doubleRunny_.swap(dr);

    transportSource_->setSource(doubleRunny_.get());
    songDial_.setLength(doubleRunny_->getTotalLength() / SAMPLE_RATE);

    trash::discard(&dr);
  }
}

static const int BUFFERY_READAHEAD = 10000;

void MainPage::operator()(const float& time) {
  if (!doubleRunny_)
    return;

  Buffery* buffery = doubleRunny_->buffery();
  buffery->setPosition(SAMPLE_RATE * time);
  if (buffery->waitUntilFilled(BUFFERY_READAHEAD))
    transportSource_->setPosition(stretchy_->get().time_scale() * time);
  else
    LOG(ERROR) << "Failed to fill buffer.";
}

}  // namespace slow
}  // namespace rec

