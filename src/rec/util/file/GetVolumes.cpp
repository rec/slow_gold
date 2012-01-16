#include <algorithm>

#include "rec/util/file/GetVolumes.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/file/Util.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {

namespace {

void add(VirtualFile::Type type, const string& name, VirtualFileList* volumes) {
  VirtualFile* vf = volumes->add_file();
  vf->set_type(type);
  vf->set_volume_name(name);
}

void addFileRoots(VirtualFileList* volumes) {
  juce::Array<File> roots;

#if JUCE_MAC
  add(VirtualFile::VOLUME, "", volumes);

  File("/Volumes").findChildFiles(roots, File::findFilesAndDirectories, false);
#else

  File::findFileSystemRoots(roots);
#endif

  for (int i = 0; i < roots.size(); ++i) {
    if (roots[i].isOnHardDisk() && roots[i].getLinkedTarget() == roots[i]) {
      string s(str(roots[i].getFullPathName()));;
      eraseVolumePrefix(&s);
      add(VirtualFile::VOLUME, s, volumes);
    }
  }
}

void addAudioCDs(VirtualFileList* volumes) {
  StringArray names = AudioCDReader::getAvailableCDNames();
  for (int i = 0; i < names.size(); ++i) {
    ptr<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
    if (!reader)
      LOG(ERROR) << "Couldn't create reader for " << names[i];
    else if (!reader->isCDStillPresent())
      continue;
    else if (!reader->getNumTracks())
      LOG(ERROR) << "No tracks for " << names[i];
    else
      add(VirtualFile::CD, str(cd::getCDKey(reader.get())), volumes);
  }
}

}  // namespace

#if 0

VirtualFileList getVolumes() {
  VirtualFileList volumes;

  add(VirtualFile::MUSIC, "", &volumes);
  add(VirtualFile::USER, "", &volumes);
  addAudioCDs(&volumes);
  addFileRoots(&volumes);

  sort(&volumes);
  return volumes;
}

#endif

void fillVolumes(VirtualFileList* volumes) {
  addAudioCDs(volumes);
  sort(volumes);
}

}  // namespace file
}  // namespace util
}  // namespace rec
