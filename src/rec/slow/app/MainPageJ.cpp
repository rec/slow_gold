#include "rec/slow/MainPageJ.h"

#include "rec/slow/MainPageK.h"
#include "rec/widget/status/Time.pb.h"
#include "rec/widget/tree/Root.h"

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

}  // namespace

MainPageJ::MainPageJ(AudioDeviceManager& deviceManager)
    : peer_(&deviceManager),
      waveform_(WaveformProto()),
      startStopButton_(String::empty),
      treeRoot_(NodeDesc()),
      explanation_(String::empty, T("<Explanation here>.")),
      loopingButton_(T("looping button")),
      timeScaleSlider_(T("Time Scale")),
      pitchScaleSlider_(T("Pitch Scale")),
      songTime_(Text()),
      realTime_(Text()),
      songDial_(Dial()),
      realDial_(realTimeDial()),
{
  startStopButton_.setButtonText(T("Play/Stop"));
  startStopButton_.addButtonListener(this);
  startStopButton_.setColour(TextButton::buttonColourId, Colour(0xff79ed7f));

  explanation_->setFont(Font(14.0000f, Font::plain));
  explanation_->setJustificationType(Justification::bottomRight);
  explanation_->setEditable(false, false, false);
  explanation_->setColour(TextEditor::textColourId, Colours::black);
  explanation_->setColour(TextEditor::backgroundColourId, Colour(0x0));

  loopingButton_->setButtonText(T("Loop sample?"));
  loopingButton_->addButtonListener(this);
  loopingButton_->setToggleState(true, false);

  timeScaleSlider_->setTooltip(T("Drag this to set the slowdown."));
  timeScaleSlider_->setRange(0.5, 5, 0);
  timeScaleSlider_->setSliderStyle(Slider::LinearHorizontal);
  timeScaleSlider_->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  timeScaleSlider_->addListener(peer_);

  pitchScaleSlider_->setTooltip(T("Drag this to set the pitchscale."));
  pitchScaleSlider_->setRange(0.125, 4, 0);
  pitchScaleSlider_->setSliderStyle(Slider::LinearHorizontal);
  pitchScaleSlider_->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
  pitchScaleSlider_->addListener(peer_);

  addAndMakeVisible(&waveform_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(&treeRoot_);
  addAndMakeVisible(&explanation_);
  addAndMakeVisible(&loopingButton_);
  addAndMakeVisible(&timeScaleSlider_);
  addAndMakeVisible(&pitchScaleSlider_);
  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&realTime_);
  addAndMakeVisible(&songDial_);
  addAndMakeVisible(&realDial_);

  setSize(600, 400);
  peer_.construct(this);
}

MainPageJ::~MainPageJ() {
  peer_.destruct();
}

void MainPageJ::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

void MainPageJ::resized() {
  waveform_->setBounds(16, getHeight() - 221, getWidth() - 32, 123);
  startStopButton_.setBounds(16, getHeight() - 46, 150, 32);
  treeRoot_.setBounds(16, 8, getWidth() - 32, getHeight() - 245);
  explanation_->setBounds(224, getHeight() - 42, getWidth() - 248, 32);
  loopingButton_->setBounds(192, getHeight() - 40, 150, 24);
  timeScaleSlider_->setBounds(300, getHeight() - 90, 200, 24);
  pitchScaleSlider_->setBounds(300, getHeight() - 60, 200, 24);
  songTime_->setBounds(520, getHeight() - 90, 110, 22);
  realTime_->setBounds(520, getHeight() - 50, 110, 22);
  songDial_->setBounds(640, getHeight() - 90, 36, 36);
  realDial_->setBounds(640, getHeight() - 50, 36, 36);
}

void MainPageJ::buttonClicked(Button* buttonThatWasClicked) {
  if(buttonThatWasClicked == &startStopButton_)
    peer_.startStopButtonClicked();
}

}  // namespace slow
}  // namespace rec

