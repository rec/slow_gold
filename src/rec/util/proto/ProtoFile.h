#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

class MessageMaker;

Message* readProtoFile(const File&, const MessageMaker&);
void writeProtoFile(const Message&, const File&);

}  // namespace util
}  // namespace rec

