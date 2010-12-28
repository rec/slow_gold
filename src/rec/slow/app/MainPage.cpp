#include <google/protobuf/descriptor.h>

#include "rec/slow/app/MainPage.h"

#include "rec/gui/RecentFiles.h"
#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/file/Util.h"

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
    explanation_(String::empty, T("<Explanation here>.")),
    timeScaleSlider_("Time Scale", Address("time_scale"), "timestretch"),
    pitchScaleSlider_("Pitch Scale", Address("pitch_scale"), "timestretch"),
    songTime_(Text()),
    songDial_(realTimeDial()),
    stretchy_(NULL),
    timeLocker_(new TimeLocker(CHANGE_LOCKER_WAIT)),
    fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)),
    fileListener_(file::getCurrentFileData()->setter()) {
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

  addAndMakeVisible(&waveformTarget_);
  waveformTarget_.addAndMakeVisible(&waveform_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(&treeRootTarget_);
  treeRootTarget_.addAndMakeVisible(treeRoot_->treeView());
  addAndMakeVisible(&explanation_);
  addAndMakeVisible(&timeScaleSlider_);
  addAndMakeVisible(&pitchScaleSlider_);
  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);

  cursor_ = waveform_.addCursor(CursorProto(), 0.0f);

  startStopButton_.addListener(this);
  waveform_.addListener(this);
  treeRoot_->addListener(&fileListener_);
  // treeRootTarget_.addListener(&fileListener_);
  waveformTarget_.addListener(&fileListener_);

  transportSource_->addListener(&songDial_);
  transportSource_->addListener(&songTime_);
  transportSource_->addListener(cursor_);

  treeRoot_->startThread();

  fileLocker_->addListener(this);
  timeLocker_->addListener(this);
  transportSource_->addListener(timeLocker_.get());

  fileLocker_->startThread();
  timeLocker_->startThread();
  file::getCurrentFileData()->addListener(fileLocker_.get());
  file::getCurrentFileData()->requestUpdate();
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::resized() {
  waveformTarget_.setBounds(16, getHeight() - 221, getWidth() - 32, 123);
  startStopButton_.setBounds(16, getHeight() - 46, 150, 32);
  treeRootTarget_.setBounds(16, 8, getWidth() - 32, getHeight() - 245);
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
    file_ = file;
    timeScaleSlider_.setData(NULL);
    pitchScaleSlider_.setData(NULL);
    timeLocker_->initialize(0);
    transportSource_->clear();
    cursor_->setTime(0.0f);

    if (empty(file_))
      return;

    stretchy_ = persist::getApp()->getData<StretchyProto>(file_, "timestretch");

    thread_ptr<DoubleRunnyBuffer> dr(new DoubleRunnyBuffer(file_, stretchy_));
    if (dr->empty())
      return;

    timeScaleSlider_.setData(stretchy_);
    pitchScaleSlider_.setData(stretchy_);

    waveform_.setAudioThumbnail(dr->cachedThumbnail()->thumbnail());
    dr->cachedThumbnail()->addListener(&waveform_);
    doubleRunny_.swap(dr);

    transportSource_->setSource(doubleRunny_.get());
    songDial_.setLength(doubleRunny_->getTotalLength() / SAMPLE_RATE);
    gui::addRecentFile(file_);
  }
}

void MainPage::operator()(const float& time) {
  // DLOG(INFO) << "Callback on time " << time;
  if (!doubleRunny_)
    return;

  else if (doubleRunny_->fillFromPosition(SAMPLE_RATE * time))
    transportSource_->setPosition(stretchy_->get().time_scale() * time);

  else
    LOG(ERROR) << "Failed to fill buffer.";
}

}  // namespace slow
}  // namespace rec

