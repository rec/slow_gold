#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace file {

bool isHidden(const File& file);
bool isAudio(const File& file);
bool isAudioOrDirectory(const File& file);

typedef bool Filter(const File& file);

bool sortedChildren(const File& f, juce::Array<File>* files,
                    Filter* filter = &isAudioOrDirectory);

void eraseVolumePrefix(string* name, bool diskToo = true);

const char** const audioExtensions();
int audioExtensionCount();

const String& audioFilePatterns();

}  // namespace file
}  // namespace util
}  // namespace rec

