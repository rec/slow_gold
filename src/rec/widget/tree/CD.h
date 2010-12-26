#ifndef __REC_WIDGET_TREE_CD__
#define __REC_WIDGET_TREE_CD__

#include "rec/util/cd/Album.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace widget {
namespace tree {

class CD : public Directory {
 public:
  CD(const NodeDesc& d, const VolumeFile& vf) : Directory(d, vf) {}

  virtual int minPartition() const { return 100; }

  virtual void computeChildren() {
    string name = "<Unknown>";
    std::vector<string> tracks;

    const string& cdKey = volumeFile_.volume().name();
    ptr<AudioCDReader> reader(cd::getAudioCDReader(cdKey.c_str()));
    if (reader) {
      cd::TrackOffsets trackOffsets = reader->getTrackOffsets();
      cd::Album album = cd::getAlbum(volumeFile_, trackOffsets);
      if (!album.track_size()) {
        int audioTracks = cd::getAudioTrackCount(*reader);
        for (int i = 0; i < audioTracks; ++i)
          tracks.push_back(String(i).toCString());

      } else {
        name = album.title() + " / " + album.artist();
        for (int i = 0; i < album.track_size(); ++i) {
          const cd::Track& track = album.track(i);
          tracks.push_back(track.artist().empty() ? track.title() :
                           track.artist() + " / " + track.title());
        }
      }
    } else {
      LOG(ERROR) << "Tried to computeCDChildren but no reader";
    }

    resetChildren();
    name_ = name.c_str();

    VolumeFile vf(volumeFile_);
    string* path = vf.add_path();
    for (int i = 0; i < tracks.size(); ++i) {
      *path = String(i).toCString();
      thread::callAsync(this, &Directory::addNode,
                        new Node(desc_, vf, tracks[i].c_str()));
    }
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CD);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_CD__
