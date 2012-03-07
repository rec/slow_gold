#include <algorithm>

#include "rec/app/Files.h"
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

void addAudioCDs(VirtualFileList* volumes) {
  StringArray names = AudioCDReader::getAvailableCDNames();
  StringArray keys;
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

  app::getAppFile("OpenCDs.txt").replaceWithText(str(volumes->DebugString()));
}

}  // namespace

void fillVolumes(VirtualFileList* volumes) {
  addAudioCDs(volumes);
  sort(volumes);
}

}  // namespace file
}  // namespace util
}  // namespace rec
