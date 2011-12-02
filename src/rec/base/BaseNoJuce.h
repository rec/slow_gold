#ifndef __REC_BASE_BASE__
#define __REC_BASE_BASE__

#include <string>
#include <vector>

#include <glog/logging.h>

#include "rec/base/disallow.h"
#include "rec/base/types.h"

namespace google { namespace protobuf { class Message; }}

namespace rec {

namespace util { namespace listener {}}
namespace util { namespace file { class VirtualFile; }}
namespace util { namespace file { class VirtualFileList; }}

typedef std::string string;
typedef unsigned int uint;

typedef google::protobuf::Message Message;

using namespace util::listener;
using namespace util;

using util::file::VirtualFile;
using util::file::VirtualFileList;

using std::vector;
using std::pair;

// Useful all over.

enum Orientation {HORIZONTAL, VERTICAL};

inline Orientation inverse(Orientation o) {
  return (o == HORIZONTAL) ? VERTICAL : HORIZONTAL;
}

enum Endianness { LITTLE_END, BIG_END };

class None {};

typedef vector<float> LevelVector;

}  // namespace rec

#endif  // __REC_BASE_BASENOJUCE__
