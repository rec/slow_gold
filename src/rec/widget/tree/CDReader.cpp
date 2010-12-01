#include <glog/logging.h>

#include "rec/widget/tree/CDReader.h"

#include "JuceLibraryCode/JuceHeader.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {

AudioCDReader* getCDReader(const string& idString) {
  int id = String(idString.c_str()).getHexValue32();
  StringArray names = AudioCDReader::getAvailableCDNames();
  int size = names.size();
  for (int i = 0; i < size; ++i) {
    scoped_ptr<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
    if (!reader)
      LOG(ERROR) << "Couldn't create reader for " << names[i].toCString();
    else if (reader->getCDDBId() == id)
      return reader.transfer();
  }
  LOG(ERROR) << "Couldn't find an AudioCDReader for ID " << id;
  return NULL;
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
