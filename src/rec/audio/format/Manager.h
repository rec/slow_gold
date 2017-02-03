#pragma once

#include "rec/audio/format/RegisterFormats.h"

namespace rec {
namespace audio {
namespace format {

AudioFormatManager* getReaderAudioFormatManager();
AudioFormatManager* getWriterAudioFormatManager();

AudioFormatReader* createReader(const File&);
AudioFormatReader* createReader(const String&);
AudioFormatWriter* createWriter(const File&);

}  // namespace format
}  // namespace audio
}  // namespace rec
