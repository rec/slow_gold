#include "rec/widget/tree/CD.h"
#include "rec/util/cd/Album.h"

namespace rec {
namespace widget {
namespace tree {

void CD::computeChildren() {
  name_ = "<Unknown CD>";
  std::vector<string> tracks;

  const string& cdKey = virtualFile_.name();
  ptr<AudioCDReader> reader(cd::getAudioCDReader(str(cdKey)));
  if (reader) {
    cd::TrackOffsets trackOffsets = reader->getTrackOffsets();
    music::Album album = cd::getCachedAlbum(virtualFile_, trackOffsets);
    if (!album.track_size()) {
      int audioTracks = cd::getAudioTrackCount(*reader);
      for (int i = 0; i < audioTracks; ++i)
        tracks.push_back(str(String(i)));

      name_ = "Unknown CD: ID = 0x" + cd::getCDKey(reader.get()).upToFirstOccurrenceOf("-", false, false);

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
    LOG(ERROR) << "Tried to computeCDChildren but no reader";
  }

  resetChildren();

  VirtualFile vf(virtualFile_);
  string* path = vf.add_path();
  for (uint32 i = 0; i < tracks.size(); ++i) {
    *path = str(String(i));
    ptr<Node> node(new Node(desc_, vf, tracks[i].c_str()));  // TODO
    listenTo(node.get());
    thread::callAsync(this, &TreeViewItem::addSubItem, node.transfer(), -1);
  }
  setProcessing(false);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
