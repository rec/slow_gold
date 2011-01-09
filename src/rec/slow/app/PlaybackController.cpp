#include "rec/slow/app/PlaybackController.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/Color.h"
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

PlaybackController::PlaybackController()
    : Layout(VERTICAL, true, "Main controls"),
      songData_("SongData") {
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

  addAndMakeVisible(&timeController_);
  addAndMakeVisible(&songData_);
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

void PlaybackController::operator()(const VolumeFile& file) {
  songData_.setData(empty(file) ? NULL : persist::data<cd::Metadata>(file));
}

void PlaybackController::setData(Data* data) {
  DataListener<StretchyProto>::setData(data);
  stretchyController_.setData(data);
}

void PlaybackController::resized() {
  songData_.setBounds(120, 8, 370, getHeight() - 16);
  stretchyController_.setBounds(500, 0, getWidth() - 500, 85);
  timeController_.setBounds(8, 8, getHeight() - 16, 100);
}

}  // namespace slow
}  // namespace rec
