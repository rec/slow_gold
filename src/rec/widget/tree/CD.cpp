#include "rec/widget/tree/CD.h"

#include "rec/base/Trans.h"
#include "rec/util/cd/Album.h"

namespace rec {
namespace widget {
namespace tree {

namespace {

TRTR(UNKNOWN_CD, "<Unknown CD>");
TRTR(UNKNOWN_CD_FULL, "Unknown CD: ID = 0x");

}  // namespace

void CD::computeChildren() {
  name_ = UNKNOWN_CD;
  std::vector<string> tracks;

  const string& cdKey = virtualFile_.volume_name();
  ptr<AudioCDReader> reader(cd::getAudioCDReader(str(cdKey)));
  if (reader) {
    cd::TrackOffsets trackOffsets = reader->getTrackOffsets();
    music::Album album = cd::getCachedAlbum(virtualFile_, trackOffsets);
    if (!album.track_size()) {
      int audioTracks = cd::getAudioTrackCount(*reader);
      for (int i = 0; i < audioTracks; ++i)
        tracks.push_back(str(String(i + 1)));

      name_ = UNKNOWN_CD_FULL +
        cd::getCDKey(reader.get()).upToFirstOccurrenceOf("-", false, false);

    } else {
      const music::Metadata& data = album.album();
      name_ = str(data.album_title() + " / " + data.artist());
      for (int i = 0; i < album.track_size(); ++i) {
        const music::Metadata& track = album.track(i);
        tracks.push_back(track.artist().empty() ? track.track_title() :
                         track.artist() + " / " + track.track_title());
      }
    }
  } else {
    LOG(DFATAL) << "Tried to computeCDChildren but no reader";
  }

  resetChildren();

  VirtualFile vf(virtualFile_);
  string* path = vf.add_path();
  for (uint32 i = 0; i < tracks.size(); ++i) {
    *path = str(String(i + 1));
    ptr<Node> node(new Node(desc_, vf, tracks[i].c_str()));  // TODO
    node->addListener(this);

    MessageManagerLock l;
    addSubItem(node.transfer(), -1);
  }
  setProcessing(false);

  MessageManagerLock l;
  setOpen(true);
}

void CD::registerAllTranslations() {
  UNKNOWN_CD.registerTranslation();
  UNKNOWN_CD_FULL.registerTranslation();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
