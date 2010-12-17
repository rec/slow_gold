#include "rec/slow/app/MainPage.h"

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
    : waveform_(WaveformProto()),
      startStopButton_(String::empty),
      treeRoot_(new Root(NodeDesc())),
      explanation_(String::empty, T("<Explanation here>.")),
      timeScaleSlider_(slow::prefs(),
                       Address("track", "timestretch", "time_scale"),
                       T("Time Scale")),
      pitchScaleSlider_(slow::prefs(),
                        Address("track", "timestretch", "pitch_scale"),
                        T("Pitch Scale")),
      songTime_(Text()),
      songDial_(realTimeDial()),
      transportSource_(&deviceManager),
      changeLocker_(new ChangeLocker<Preferences>(CHANGE_LOCKER_WAIT)),
      fileListener_(slow::prefs()->setter(), Address("track", "file")) {
  setSize(600, 400);

  startStopButton_.setButtonText(T("Play/Stop"));
  startStopButton_.setColour(TextButton::buttonColourId, Colour(0xff79ed7f));

  explanation_.setFont(Font(14.0000f, Font::plain));
  explanation_.setJustificationType(Justification::bottomRight);
  explanation_.setEditable(false, false, false);
  explanation_.setColour(TextEditor::textColourId, Colours::black);
  explanation_.setColour(TextEditor::backgroundColourId, Colour(0x0));

  timeScaleSlider_.setTooltip(T("Drag this to set the slowdown."));
  timeScaleSlider_.setRange(0.5, 5, 0);
  timeScaleSlider_.setSliderStyle(Slider::LinearHorizontal);
  timeScaleSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);

  pitchScaleSlider_.setTooltip(T("Drag this to set the pitchscale."));
  pitchScaleSlider_.setRange(0.125, 4, 0);
  pitchScaleSlider_.setSliderStyle(Slider::LinearHorizontal);
  pitchScaleSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);

  addAndMakeVisible(&waveform_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(treeRoot_.get());
  addAndMakeVisible(&explanation_);
  addAndMakeVisible(&timeScaleSlider_);
  addAndMakeVisible(&pitchScaleSlider_);
  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);

  cursor_ = waveform_.addCursor(CursorProto(), 0.0f);

  changeLocker_->addListener(this);
  slow::prefs()->addListener(changeLocker_.get());
  startStopButton_.addButtonListener(this);
  treeRoot_->addListener(&fileListener_);

  transportSource_.addChangeListener(&songDial_);
  transportSource_.addChangeListener(&songTime_);
  transportSource_.addChangeListener(cursor_);

  treeRoot_->startThread();
  changeLocker_->startThread();
  slow::prefs()->requestUpdate();
}

MainPage::~MainPage() {
  changeLocker_->removeListener(this);
  slow::prefs()->removeListener(changeLocker_.get());
  startStopButton_.removeButtonListener(this);
  treeRoot_->removeListener(&fileListener_);

  transportSource_.removeChangeListener(&songDial_);
  transportSource_.removeChangeListener(&songTime_);
  transportSource_.removeChangeListener(cursor_);

  trash::discard(changeLocker_.transfer());
  trash::discard(treeRoot_.transfer());
  trash::discard(doubleRunny_.transfer());
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPage::resized() {
  waveform_.setBounds(16, getHeight() - 221, getWidth() - 32, 123);
  startStopButton_.setBounds(16, getHeight() - 46, 150, 32);
  treeRoot_->setBounds(16, 8, getWidth() - 32, getHeight() - 245);
  explanation_.setBounds(224, getHeight() - 42, getWidth() - 248, 32);
  timeScaleSlider_.setBounds(300, getHeight() - 90, 200, 24);
  pitchScaleSlider_.setBounds(300, getHeight() - 60, 200, 24);
  songTime_.setBounds(520, getHeight() - 90, 110, 22);
  songDial_.setBounds(640, getHeight() - 90, 36, 36);
}

void MainPage::buttonClicked(Button* buttonThatWasClicked) {
  transportSource_.toggle();
}

static const int BLOCKSIZE = 1024;

void MainPage::operator()(const Preferences& prefs) {
  const VolumeFile& file = prefs.track().file();
  if (prefs_.track().file() != file) {
    transportSource_.stop();
    transportSource_.setPosition(0);
    transportSource_.setSource(NULL);

    scoped_ptr<DoubleRunnyBuffer> dr(new DoubleRunnyBuffer(file, BLOCKSIZE));
    dr->setPreferences(prefs);
    dr->startThread();
    waveform_.setAudioThumbnail(dr->thumbnail());
    doubleRunny_.swap(dr);
    transportSource_.setSource(doubleRunny_.get());
    trash::discard(dr.transfer());

  } else if (doubleRunny_) {
    float ratio = prefs.track().timestretch().time_scale() /
      prefs_.track().timestretch().time_scale();
    int position = transportSource_.getNextReadPosition();
    doubleRunny_->setPreferences(prefs, position, ratio);
  }

  prefs_ = prefs;
}

}  // namespace slow
}  // namespace rec

