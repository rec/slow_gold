#include "rec/audio/format/Manager.h"
#include "rec/audio/format/mpg123/Format.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace format {

namespace {

using namespace juce;

AudioFormatManager* getInstance() {
  format::mpg123::initializeOnce();
  ptr<AudioFormatManager> afm(new AudioFormatManager());
  // afm->registerFormat(new format::mpg123::Format(), false);
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

AudioFormatReader* createReader(const String& f) {
  return createReader(File(f));
}

AudioFormatWriter* createWriter(const File& f) {
  const String ext = f.getFileExtension();
  AudioFormat* fmt = getAudioFormatManager()->findFormatForFileExtension(ext);
  if (!fmt) {
    LOG(ERROR) << "Unable to open file " << str(f);
    return NULL;
  }

  f.deleteFile();
  ptr<FileOutputStream> fos(new FileOutputStream(f));
  StringArray qualityOptions = fmt->getQualityOptions();
  int quality = std::max(0, qualityOptions.size() - 1);

  ptr<AudioFormatWriter> writer(fmt->createWriterFor(fos.transfer(), 44100.0, 2, 16,
                                                     StringPairArray(),
                                                     quality));
  if (!writer)
    LOG(ERROR) << "Couldn't create writer for " << str(f);
  return writer.transfer();
}

}  // namespace format
}  // namespace audio
}  // namespace rec

