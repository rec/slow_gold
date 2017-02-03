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
    static auto instance = std::unique_ptr<AudioFormatManager>(
        createAudioFormatManager(READ));
    return instance.get();
}

AudioFormatManager* getWriterAudioFormatManager() {
    static auto instance = std::unique_ptr<AudioFormatManager>(
        createAudioFormatManager(WRITE));
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
    auto fmt = getWriterAudioFormatManager()->
        findFormatForFileExtension(ext);

    if (!fmt) {
        LOG(ERROR) << "Unable to open file " << str(f);
        return nullptr;
    }

    f.deleteFile();
    auto fos = std::make_unique<FileOutputStream>(f);
    auto qualityOptions = fmt->getQualityOptions();
    auto quality = std::max(0, qualityOptions.size() - 1);
    auto channels = 2;
    auto sampleRate = static_cast<double>(getOutputSampleRate());

    auto writer = std::unique_ptr<AudioFormatWriter>(
        fmt->createWriterFor(fos.release(), sampleRate,
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
