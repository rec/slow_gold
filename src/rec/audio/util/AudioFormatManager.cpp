#include "rec/audio/util/AudioFormatManager.h"
#include "rec/audio/format/mpg123/Format.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {

namespace {

AudioFormatManager* getInstance() {
  format::mpg123::initializeOnce();
  ptr<AudioFormatManager> afm(new AudioFormatManager());
  afm->registerFormat(new format::mpg123::Format(), false);
  afm->registerBasicFormats();

  return afm.transfer();
}

}  // namespace

AudioFormatManager* getAudioFormatManager() {
  static ptr<AudioFormatManager> instance(getInstance());
  return instance.get();
}

AudioFormatReader* createReader(const File& f) {
  return getAudioFormatManager()->createReaderFor(f);
}

AudioFormatReader* createReader(const String& f) { return createReader(File(f)); }

}  // namespace audio
}  // namespace rec
