#include <algorithm>

#include "rec/app/Files.h"
#include "rec/util/file/GetVolumes.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/file/CompareFile.h"
#include "rec/util/file/Util.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {

namespace {

void add(VirtualFile::Type type, const string& key, const String& cdName,
         VirtualFileList* volumes) {
  VirtualFile* vf = volumes->add_file();
  vf->set_type(type);
  vf->set_volume_name(key);
  vf->set_cd_name(str(cdName));
}

void addAudioCDs(VirtualFileList* volumes) {
  StringArray names = AudioCDReader::getAvailableCDNames();
  for (int i = 0; i < names.size(); ++i) {
    ptr<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
    if (reader && reader->isCDStillPresent() && reader->getNumTracks()) {
      string key = str(cd::getCDKey(reader.get()));
      if (key.size())
        add(VirtualFile::CD, key, names[i], volumes);
    }
  }
}

}  // namespace

void fillVolumes(VirtualFileList* volumes) {
  addAudioCDs(volumes);
  sort(volumes);
}

}  // namespace file
}  // namespace util
}  // namespace rec
