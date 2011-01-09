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

PlaybackController::PlaybackController()
    : Layout(VERTICAL, true, "Main controls"),
      transportSource_(NULL),
      startStopButton_("Start stop button", juce::DrawableButton::ImageFitted),
      songTime_(Text()),
      songDial_(realTimeDial()),
      songData_("SongData") {
  startStopButton_.setImages(gui::icon::MediaPlaybackStart::get(),
                             NULL, NULL, NULL,
                             gui::icon::MediaPlaybackStop::get());
  startStopButton_.setClickingTogglesState(true);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(&stretchyController_);

  songData_.add("Track", Address("track_title"),
                "The name of the individual track.");
  songData_.add("Album", Address("album_title"),
                "The name of the album this track is from, if any.");
  songData_.add("Artist", Address("artist"),
                "The creator of this specific track");
  songData_.add("Number", Address("track_number"),
                "If this was from a CD, which track was it?");
  songData_.add("Notes", Address("notes"), "Put whatever you like here");
  songData_.addToLayoutManager();

  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);
  addAndMakeVisible(&songData_);

  startStopButton_.addListener(this);
}

void PlaybackController::setTransport(AudioTransportSourcePlayer* source) {
  if (transportSource_) {
    transportSource_->removeListener(&songDial_);
    transportSource_->removeListener(&songTime_);
    transportSource_->changeBroadcaster()->removeListener(this);
  }

  transportSource_ = source;

  if (transportSource_) {
    transportSource_->addListener(&songDial_);
    transportSource_->addListener(&songTime_);
    transportSource_->changeBroadcaster()->addListener(this);
  }
}

void PlaybackController::operator()(float time) {
  if (getData())
    broadcast(time / getData()->get().time_scale());
}

void PlaybackController::operator()(const StretchyProto& desc) {
  thread::callAsync(&stretchyController_, 
                    &gui::StretchyController::enableSliders,
                    !desc.disabled());
}

void PlaybackController::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    transportSource_->toggle();
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
  stretchyController_.setData(data);
}

void PlaybackController::resized() {
  startStopButton_.setBounds(8, 8, 32, 32);
  songData_.setBounds(120, 8, 370, getHeight() - 16);
  stretchyController_.setBounds(500, 0, getWidth() - 500, 85);

  songTime_.setBounds(getWidth() - 120, 60, 110, 22);
  songDial_.setBounds(getWidth() - 46, 90 - 46, 36, 36);
}

void PlaybackController::operator()(const VolumeFile& file) {
  songData_.setData(empty(file) ? NULL : persist::data<cd::Metadata>(file));
}

}  // namespace slow
}  // namespace rec
