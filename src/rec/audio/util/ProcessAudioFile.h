#pragma once

#include "rec/audio/Audio.h"

namespace rec {
namespace audio {
namespace util {

// Filters a source to provide another source.
using SourceFilter = Source* (*)(Source*);
using SourceAndWriter = std::pair<Source*, AudioFormatWriter*>;

void processAudioFile(const File& in, const File& out, SourceFilter f);
SourceAndWriter makeSourceAndWriter(const File& in, const File& out);

}  // namespace util
}  // namespace audio
}  // namespace rec
