#pragma once

#include "rec/base/base.h"

namespace rec {
namespace slow {

enum SaveOrOpen {SAVE_FILE, OPEN_FILE};

File browseForFile(const String& msg, const File& startFile, SaveOrOpen save,
                                      const String& fileFilter = "*");

}  // namespace slow
}  // namespace rec
