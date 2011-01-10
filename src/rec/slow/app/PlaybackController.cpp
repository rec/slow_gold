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
    : Layout("Main controls"),
      timeControllerResizer_(Address("clock_x"), this, 1),
      songData_("SongData"),
      songDataResizer_(Address("songdata_x"), this, 3),
      panel_("Main panel", VERTICAL),
      stretchyResizer_(Address("stretchy_y"), &panel_, 1),
      transport_("tranport goes here") {
  songData_.add("Track", Address("track_title"),
                "The name of the individual track.");
  songData_.add("Album", Address("album_title"),
                "The name of the album this track is from, if any.");
  songData_.add("Artist", Address("artist"),
                "The creator of this specific track");
  songData_.add("Number", Address("track_number"),
                "If this was from a CD, which track was it?");
  songData_.add("Year", Address("year"),
                "What year was this track recorded?");
  songData_.add("Genre", Address("genre"),
                "Tags that categorize this track.");
  songData_.add("Notes", Address("notes"), "Put whatever you like here")->
      editor()->setMultiLine(true, true);

  addToLayout(&timeController_);
  timeControllerResizer_.add(5);
  addToLayout(&songData_);
  songDataResizer_.add(5);
  addToLayout(&panel_);

  panel_.addToLayout(&stretchyController_);
  stretchyResizer_.add(5);
  panel_.addToLayout(&transport_);
}

void PlaybackController::setLayoutData() {
  persist::Data<AppLayout>* data = persist::data<AppLayout>();

  timeControllerResizer_.setSetter(data);
  songDataResizer_.setSetter(data);
  stretchyResizer_.setSetter(data);
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

}  // namespace slow
}  // namespace rec
