#ifndef __REC_UTIL_FILEUTIL__
#define __REC_UTIL_FILEUTIL__

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

String audioFilePatterns();

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILEUTIL__
