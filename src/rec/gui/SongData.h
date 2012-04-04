#ifndef __REC_GUI_SONGDATA__
#define __REC_GUI_SONGDATA__

#include "rec/data/Data.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/gui/SetterTextArea.h"
#include "rec/music/Metadata.h"
#include "rec/util/Cuttable.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace gui {

class SongData : public SetterTextArea,
                 public Cuttable,
                 public UntypedDataListener {
 public:
  typedef data::Address Address;

  explicit SongData(MenuBarModel*)
    : UntypedDataListener(getTypeName<music::Metadata>()) {
    const string& typeName = getTypeName<music::Metadata>();
    setName("SongData");
    add(trans("Track"), typeName,
        Address("track_title"),
        trans("Track Title: The name of this track."));
    add(trans("Album"), typeName,
        Address("album_title"),
        trans("Album Name: The name of the album this track is from."));
    add(trans("Artist"), typeName,
        Address("artist"),
        trans("Artist Name: The artist or musician who made this specific track"));
    add(trans("Number"), typeName,
        Address("track_number"),
        trans("Track Number: The album track number for this track"));
    add(trans("Year"), typeName,
        Address("year"),
        trans("Album Year: The year that that this track was recorded."));
    add(trans("Genre"), typeName,
        Address("genre"),
        trans("Track tags: Tags that categorize this track."));
    add(trans("Notes"), typeName,
        Address("notes"),
        trans("Track Notes: You can enter your notes here."))->
        editor()->setMultiLine(true, true);
  }

  virtual void startListening() {
    SetterTextArea::startListening();
    UntypedDataListener::startListening();
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
