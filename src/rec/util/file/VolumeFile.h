#ifndef __REC_UTIL_FILE_VIRTUALFILE__
#define __REC_UTIL_FILE_VIRTUALFILE__

#include "rec/base/base.h"
#include "rec/util/file/VolumeFile.pb.h"

namespace rec {

namespace persist {
template <typename Type> class Data;
}  // namespace persist

namespace util {
namespace file {

const File getVolume(const Volume& volume);
const File getFile(const VolumeFile& file);

const File getShadowDirectory(const Volume& volume);
const File getShadowDirectory(const VolumeFile& file);

template <typename Proto>
const File getShadowFile(const Proto& pr, const String& child) {
  return getShadowDirectory(pr).getChildFile(child);
}

const String getFilename(const VolumeFile& file);
const String getDisplayName(const VolumeFile& file);
const String getFullDisplayName(const VolumeFile& file);

bool compareVolumes(const Volume& x, const Volume& y);
bool compareVolumeFiles(const VolumeFile& x, const VolumeFile& y);

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
bool empty(const VolumeFile& file);

typedef persist::Data<VolumeFile> VolumeFileData;

VolumeFile toVolumeFile(const File& file);

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_VIRTUALFILE__
