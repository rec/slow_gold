#pragma once

#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

using Type = VirtualFile::Type;

struct Compare {
    bool operator()(Type x, Type y) const { return x > y; }
};

using SpecialLocation = std::pair<File, const char*>;
using TypeMap = std::map<Type, SpecialLocation, Compare>;

const TypeMap& getTypeMap();

}  // namespace file
}  // namespace util
}  // namespace rec
