#ifndef __REC_GUI_SONGDATA__
#define __REC_GUI_SONGDATA__

#include "rec/util/cd/Album.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace gui {

class SongData : public gui::SetterTextArea<cd::Metadata> {
 public:
  SongData() : gui::SetterTextArea<cd::Metadata>("SongData") {
    using persist::Address;

    add("Track", Address("track_title"), "The name of the individual track.");
    add("Album", Address("album_title"),
        "The name of the album this track is from, if any.");
    add("Artist", Address("artist"), "The creator of this specific track");
    add("Number", Address("track_number"),
        "If this was from a CD, which track was it?");
    add("Year", Address("year"), "What year was this track recorded?");
    add("Genre", Address("genre"), "Tags that categorize this track.");
    add("Notes", Address("notes"), "Put whatever you like here")->
        editor()->setMultiLine(true, true);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(SongData);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SONGDATA__
