#ifndef __REC_UTIL_FILE_TYPEMAP__
#define __REC_UTIL_FILE_TYPEMAP__

#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

typedef VirtualFile::Type Type;

struct Compare {
  bool operator()(Type x, Type y) const { return x > y; }
};

typedef std::pair<File, const char*> SpecialLocation;
typedef std::map<Type, SpecialLocation, Compare> TypeMap;

const TypeMap& getTypeMap();

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_TYPEMAP__
