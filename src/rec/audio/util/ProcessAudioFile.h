#pragma once

#include "rec/audio/Audio.h"

namespace rec {
namespace audio {
namespace util {

// Filters a source to provide another source.
typedef Source* (*SourceFilter)(Source*);

void processAudioFile(const File& in, const File& out, SourceFilter f);


typedef std::pair<Source*, AudioFormatWriter*> SourceAndWriter;

SourceAndWriter makeSourceAndWriter(const File& in, const File& out);

}  // namespace util
}  // namespace audio
}  // namespace rec

