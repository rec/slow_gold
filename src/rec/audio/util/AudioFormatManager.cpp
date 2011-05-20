#include "rec/audio/util/AudioFormatManager.h"
#include "rec/audio/format/mpg123/Format.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {

namespace {

AudioFormatManager* getInstance() {
  format::mpg123::initializeOnce();
  ptr<AudioFormatManager> afm(new AudioFormatManager());
  afm->registerBasicFormats();
  afm->registerFormat(new format::mpg123::Format(), false);

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

AudioFormatReader* createReader(const VirtualFile& f) {
  return createReader(getFile(f));
}

AudioFormatReader* createReader(const String& f) { return createReader(File(f)); }
AudioFormatReader* createReader(const string& f) { return createReader(str(f)); }

}  // namespace audio
}  // namespace rec
