#ifndef __REC_WIDGET_TREE_CD__
#define __REC_WIDGET_TREE_CD__

#include "rec/util/cd/Album.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/tree/Directory.h"

namespace rec {
namespace widget {
namespace tree {

class CD : public Directory {
 public:
  CD(const NodeDesc& d, const VolumeFile& vf) : Directory(d, vf) {}

  virtual int minPartition() const { return 100; }
  virtual void itemClicked() {
    Node::itemClicked();
  }

  virtual void computeChildren() {
    name_ = "<Unknown CD>";
    std::vector<string> tracks;

    const string& cdKey = volumeFile_.name();
    ptr<AudioCDReader> reader(cd::getAudioCDReader(cdKey.c_str()));
    if (reader) {
      cd::TrackOffsets trackOffsets = reader->getTrackOffsets();
      cd::Album album = cd::getAlbum(volumeFile_, trackOffsets);
      if (!album.track_size()) {
        int audioTracks = cd::getAudioTrackCount(*reader);
        for (int i = 0; i < audioTracks; ++i)
          tracks.push_back(String(i).toCString());

        name_ = "Unknown CD: ID = 0x" + cd::getCDKey(reader.get()).upToFirstOccurrenceOf("-", false, false);

      } else {
        const cd::Metadata& data = album.album();
        name_ = (data.album_title() + " / " + data.artist()).c_str();
        for (int i = 0; i < album.track_size(); ++i) {
          const cd::Metadata& track = album.track(i);
          tracks.push_back(track.artist().empty() ? track.track_title() :
                           track.artist() + " / " + track.track_title());
        }
      }
    } else {
      LOG(ERROR) << "Tried to computeCDChildren but no reader";
    }

    resetChildren();

    VolumeFile vf(volumeFile_);
    string* path = vf.add_path();
    for (int i = 0; i < tracks.size(); ++i) {
      *path = String(i).toCString();
      ptr<Node> node(new Node(desc_, vf, tracks[i].c_str()));
      node->addListener(this);
      thread::callAsync(this, &TreeViewItem::addSubItem, node.transfer(), -1);
    }
    setProcessing(false);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CD);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_CD__
