#include <algorithm>

#include "rec/util/file/GetVolumes.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/util/file/Util.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {

namespace {

void add(Volume::Type type, const string& name, VolumeFileList* volumes) {
  Volume* vf = volumes->add_file()->mutable_volume();
  vf->set_type(type);
  vf->set_name(name);
}

void addFileRoots(VolumeFileList* volumes) {
  juce::Array<File> roots;

#if JUCE_MAC
  add(Volume::VOLUME, "", volumes);

  File("/Volumes").findChildFiles(roots, File::findFilesAndDirectories, false);
#else

  File::findFileSystemRoots(roots);
#endif

  for (int i = 0; i < roots.size(); ++i) {
    if (roots[i].isOnHardDisk() && roots[i].getLinkedTarget() == roots[i]) {
      string s(roots[i].getFullPathName().toCString());
      eraseVolumePrefix(&s);
      add(Volume::VOLUME, s, volumes);
    }
  }
}

void addAudioCDs(VolumeFileList* volumes) {
  StringArray names = AudioCDReader::getAvailableCDNames();
  for (int i = 0; i < names.size(); ++i) {
    ptr<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
    if (reader && reader->getNumTracks())
      add(Volume::CD, cd::getCDKey(reader.get()).toCString(), volumes);
    else
      LOG(ERROR) << "Couldn't create reader for " << names[i].toCString();
  }
}

}  // namespace

VolumeFileList getVolumes() {
  VolumeFileList volumes;

  add(Volume::MUSIC, "", &volumes);
  add(Volume::USER, "", &volumes);
  addAudioCDs(&volumes);
  addFileRoots(&volumes);

  std::sort(volumes.mutable_file()->begin(), 
            volumes.mutable_file()->end(), compareVolumeFiles);
  return volumes;
}

}  // namespace file
}  // namespace util
}  // namespace rec
