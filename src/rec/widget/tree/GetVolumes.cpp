#include <algorithm>

#include "rec/widget/tree/GetVolumes.h"
#include "rec/util/cd/CDReader.h"
#include "rec/widget/tree/VolumeFile.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {

namespace {

void add(Volume::Type type, const string& name, VolumeList* volumes) {
  volumes->push_back(Volume());
  volumes->back().set_type(type);
  volumes->back().set_name(name);
}

void addFileRoots(VolumeList* volumes) {
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

void addAudioCDs(VolumeList* volumes) {
  StringArray names = AudioCDReader::getAvailableCDNames();
  for (int i = 0; i < names.size(); ++i) {
    ptr<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
    if (reader)
      add(Volume::CD, cd::getCDKey(reader.get()).toCString(), volumes);
    else
      LOG(ERROR) << "Couldn't create reader for " << names[i].toCString();
  }
}

}  // namespace

VolumeList getVolumes() {
  VolumeList volumes;

  add(Volume::MUSIC, "", &volumes);
  add(Volume::USER, "", &volumes);
  addAudioCDs(&volumes);
  addFileRoots(&volumes);

  std::sort(volumes.begin(), volumes.end(), compareVolumes);
  return volumes;
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
