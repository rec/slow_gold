#pragma once

#include <string>
#include <vector>

#include <glog/logging.h>

#include "rec/base/disallow.h"
#include "rec/base/types.h"

namespace google { namespace protobuf { class Message; }}

namespace rec {

namespace util { namespace file { class VirtualFile; }}
namespace util { namespace file { class VirtualFileList; }}

typedef unsigned int uint;

typedef google::protobuf::Message Message;
typedef std::string string;

using namespace util;

using std::pair;
using std::vector;
using util::file::VirtualFile;
using util::file::VirtualFileList;

class None {};

}  // namespace rec

