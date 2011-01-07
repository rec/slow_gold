#include "rec/slow/app/PlaybackController.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/Color.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/cd/Album.h"

using namespace rec::proto::arg;

using juce::Colours;
using rec::gui::Colors;
using rec::widget::status::time::Dial;
using rec::widget::status::time::DialComponent;
using rec::widget::status::time::Text;
using rec::widget::status::time::TextComponent;

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
}  // namespace


PlaybackController::PlaybackController(AudioTransportSourcePlayer* transport)
    : Layout(VERTICAL, true, "Main controls"),
      transportSource_(transport),
      startStopButton_("Start stop button", juce::DrawableButton::ImageFitted),
      disableButton_("Disable pitch/time shift", Address("disabled")),
      songTime_(Text()),
      songDial_(realTimeDial()),
      songData_("SongData") {
  startStopButton_.setImages(gui::icon::MediaPlaybackStart::get(),
                             NULL, NULL, NULL,
                             gui::icon::MediaPlaybackStop::get());
  startStopButton_.setClickingTogglesState(true);
  addAndMakeVisible(&disableButton_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(&stretchyController_);

  songData_.add("Track", Address("track_title"));
  songData_.add("Album", Address("album_title"));
  songData_.add("Artist", Address("artist"));
  songData_.add("Track Number", Address("track_number"));
  songData_.add("Notes", Address("notes"));
  songData_.addToLayoutManager();

  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);
  addAndMakeVisible(&songData_);

  startStopButton_.addListener(this);
  disableButton_.addListener(this);

  transportSource_->addListener(&songDial_);
  transportSource_->addListener(&songTime_);
  transportSource_->changeBroadcaster()->addListener(this);
}

void PlaybackController::operator()(float time) {
  if (getData())
    broadcast(time / getData()->get().time_scale());
}

void PlaybackController::operator()(const StretchyProto& desc) {
  thread::callAsync(&stretchyController_, &Component::setEnabled,
                    !desc.disabled());
}

void PlaybackController::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    transportSource_->toggle();

  else if (button == &disableButton_ && getData())
    getData()->set("disable", disableButton_.getToggleState());
}

void PlaybackController::setLength(int length) {
  songDial_.setLength(length);
}

void PlaybackController::operator()(const AudioTransportSourcePlayer& player) {
  thread::callAsync(this, &PlaybackController::setButtonState);
}

void PlaybackController::setButtonState() {
  startStopButton_.setToggleState(transportSource_->isPlaying(), false);
  startStopButton_.repaint();
}

void PlaybackController::setData(Data* data) {
  DataListener<StretchyProto>::setData(data);
  disableButton_.setData(data);
  stretchyController_.setData(data);
  bool enable = !(data && data->get().disabled());

  if (enable != stretchyController_.isEnabled())
    thread::callAsync(&stretchyController_, &Component::setEnabled, enable);

}

void PlaybackController::resized() {
  startStopButton_.setBounds(8, 8, 32, 32);
  disableButton_.setBounds(8, 50, 100, 20);
  songData_.setBounds(120, 8, 270, getHeight() - 16);
  stretchyController_.setBounds(500, 0, getWidth() - 500, 85);

  songTime_.setBounds(getWidth() - 120, 60, 110, 22);
  songDial_.setBounds(getWidth() - 46, 90 - 46, 36, 36);
}

void PlaybackController::operator()(const VolumeFile& file) {
  songData_.setData(empty(file) ? NULL : persist::data<cd::Metadata>(file));
}

}  // namespace slow
}  // namespace rec
