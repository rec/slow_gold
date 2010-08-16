#ifndef __REC_UTIL_TESTDATA__
#define __REC_UTIL_TESTDATA__

#include "juce_amalgamated.h"

namespace rec {
namespace util {

inline String testDataPath(const String& filename) {
  return "../../../../../../data/" + filename;
}

inline File testFile(const String& filename) {
  return File("../../../../../../data/" + filename);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_TESTDATA__
