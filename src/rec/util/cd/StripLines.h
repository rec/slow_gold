#ifndef __REC_UTIL_CD_STRIPLINES__
#define __REC_UTIL_CD_STRIPLINES__

#include "rec/base/base.h"

namespace juce {
class StringArray;
}

namespace rec {
namespace util {
namespace cd {

int stripLines(String* data, juce::StringArray* lines);
bool stripLine(String* data, juce::StringArray* lines);

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_STRIPLINES__
