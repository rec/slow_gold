#ifndef __REC_GUI_SONGDATA__
#define __REC_GUI_SONGDATA__

#include "rec/app/LanguageListener.h"
#include "rec/data/Data.h"
#include "rec/data/DataListener.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/gui/SetterTextArea.h"
#include "rec/music/Metadata.h"
#include "rec/util/Cuttable.h"

namespace rec {
namespace gui {

class SongData : public app::LanguageListener,
                 public SetterTextArea,
                 public Cuttable,
                 public UntypedDataListener {
 public:
  typedef data::Address Address;

  SongData() : UntypedDataListener(getTypeName<music::Metadata>()) {
    setName("SongData");
  }

  virtual void languageChanged() {
    clear(true);
    const string& typeName = getTypeName<music::Metadata>();
    add(Trans("Track"), typeName,
        Address("track_title"),
        Trans("Track Title: The name of this track."));
    add(Trans("Album"), typeName,
        Address("album_title"),
        Trans("Album Name: The name of the album this track is from."));
    add(Trans("Artist"), typeName,
        Address("artist"),
        Trans("Artist Name: The artist or musician who made this specific track."));
    add(Trans("Number"), typeName,
        Address("track_number"),
        Trans("Track Number: The album track number for this track"));
    add(Trans("Year"), typeName,
        Address("year"),
        Trans("Album Year: The year that that this track was recorded."));
    add(Trans("Genre"), typeName,
        Address("genre"),
        Trans("Track tags: Tags that categorize this track."));
    add(Trans("Notes"), typeName,
        Address("notes"),
        Trans("Track Notes: You can enter your notes here."))->
        editor()->setMultiLine(true, true);
    resized();
  }

  virtual void operator()(const Message&) {}
  virtual bool canCopy() const { return true; }
  virtual bool canCut() const { return false; }
  virtual bool canPaste(const string&) const { return false; }
  virtual bool paste(const string&) { return false; }
  virtual const string cuttableName() const { return "SongData"; }

  virtual string copy() const {
    return yaml::write(*ptr<Message>(data::cloneMessage(getData())));
  }
  virtual void cut() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SongData);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SONGDATA__
