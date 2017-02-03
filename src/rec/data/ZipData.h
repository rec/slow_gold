#pragma once

#include "rec/base/base.h"

namespace rec {
namespace data {

// Store all data to a zip file and return that file, or no file if we failed.
File zipData(const String&);
File zipData(const File&);

bool unzipData(const File&);

}  // namespace data
}  // namespace rec

