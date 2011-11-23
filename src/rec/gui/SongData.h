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

  virtual bool canCopy() const { return true; }
  virtual bool canCut() const { return false; }
  virtual bool canPaste() const { return false; }
  virtual bool paste(const string&) { return false; }
  virtual const string cuttableName() const { return "SongData"; }
  virtual string copy() const {
    return yaml::write(data()->get());
  }
  virtual void cut() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SongData);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SONGDATA__
