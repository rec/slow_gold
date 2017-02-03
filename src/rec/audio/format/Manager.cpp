#include <algorithm>

#include "rec/audio/OutputSampleRate.h"
#include "rec/audio/format/Manager.h"
#include "rec/base/SampleRate.h"
#include "rec/base/SampleTime.h"

namespace rec {
namespace audio {
namespace format {

using namespace juce;

AudioFormatManager* getReaderAudioFormatManager() {
  static std::unique_ptr<AudioFormatManager> instance(createAudioFormatManager(READ));
  return instance.get();
}

AudioFormatManager* getWriterAudioFormatManager() {
  static std::unique_ptr<AudioFormatManager> instance(createAudioFormatManager(WRITE));
  return instance.get();
}

AudioFormatReader* createReader(const File& f) {
  return getReaderAudioFormatManager()->createReaderFor(f);
}

AudioFormatReader* createReader(const String& f) {
  return createReader(File(f));
}

AudioFormatWriter* createWriter(const File& f) {
  const String ext = f.getFileExtension();
  AudioFormat* fmt = getWriterAudioFormatManager()->
    findFormatForFileExtension(ext);

  if (!fmt) {
    LOG(ERROR) << "Unable to open file " << str(f);
    return nullptr;
  }

  f.deleteFile();
  std::unique_ptr<FileOutputStream> fos(new FileOutputStream(f));
  StringArray qualityOptions = fmt->getQualityOptions();
  int quality = std::max(0, qualityOptions.size() - 1);
  int channels = 2;
  double sampleRate = static_cast<double>(getOutputSampleRate());

  std::unique_ptr<AudioFormatWriter> writer(fmt->createWriterFor(fos.release(), sampleRate,
                                                     channels, 16,
                                                     StringPairArray(),
                                                     quality));
  if (!writer)
    LOG(ERROR) << "Couldn't create writer for " << str(f);
  return writer.release();
}

}  // namespace format
}  // namespace audio
}  // namespace rec
