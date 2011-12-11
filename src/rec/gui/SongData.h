#ifndef __REC_GUI_SONGDATA__
#define __REC_GUI_SONGDATA__

#include "rec/data/Data.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/gui/SetterTextArea.h"
#include "rec/gui/component/Focusable.h"
#include "rec/music/Metadata.h"
#include "rec/util/Cuttable.h"
#include "rec/util/DataListener.h"

namespace rec {
namespace gui {

class SongData : public component::Focusable<SetterTextArea <music::Metadata> >,
                 public Cuttable,
                 public DataListener<music::Metadata> {
 public:
  typedef data::Address Address;

  explicit SongData(MenuBarModel* model)
      : component::Focusable<SetterTextArea<music::Metadata> >(model) {
    setName("SongData");
#if 1
    add("Track", Address("track_title"), "The name of this track.");
    add("Album", Address("album_title"),
        "The name of the album this track is from.");
    add("Artist", Address("artist"),
        "The artist or musician who made this specific track");
    add("Number", Address("track_number"),
        "The album track number for this track");
    add("Year", Address("year"),
        "The year that that this track was recorded.");
    add("Genre", Address("genre"),
        "Tags that categorize this track.");
    add("Notes", Address("notes"), "Your notes here.")->
        editor()->setMultiLine(true, true);
#endif
  }

  virtual bool canCopy() const { return true; }
  virtual bool canCut() const { return false; }
  virtual bool canPaste() const { return false; }
  virtual bool paste(const string&) { return false; }
  virtual const string cuttableName() const { return "SongData"; }
  virtual string copy() const {
    return yaml::write(getProto());
  }
  virtual void cut() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SongData);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SONGDATA__
