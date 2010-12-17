#ifndef __REC_WIDGET_TREE_VIRTUALFILE__
#define __REC_WIDGET_TREE_VIRTUALFILE__

#include "rec/base/base.h"
#include "rec/widget/tree/VolumeFile.pb.h"

namespace rec {
namespace widget {
namespace tree {

const File getVolume(const Volume& volume);
const File getFile(const VolumeFile& file);

const File getShadowDirectory(const Volume& volume);
const File getShadowDirectory(const VolumeFile& file);

template <typename Proto>
const File getShadowFile(const Proto& pr, const string& child) {
  return getShadowDirectory(pr).getChildFile(child.c_str());
}

bool compareVolumes(const Volume& x, const Volume& y);

bool operator==(const Volume& x, const Volume& y);
bool operator==(const VolumeFile& x, const VolumeFile& y);

inline bool operator!=(const Volume& x, const Volume& y) {
  return !(x == y);
}

inline bool operator!=(const VolumeFile& x, const VolumeFile& y) {
  return !(x == y);
}

AudioFormatReader* createReader(const VolumeFile& file);
PositionableAudioSource* createSource(const VolumeFile& file);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_VIRTUALFILE__
