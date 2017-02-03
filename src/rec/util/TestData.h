#pragma once

#include "rec/base/base.h"

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

