#pragma once

#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

VirtualFile move(const VirtualFile&,
                 const string& dialogName,
                 const String& dialogTitle);

VirtualFile copy(const VirtualFile&,
                 const string& dialogName,
                 const String& dialogTitle);


}  // namespace data
}  // namespace rec
