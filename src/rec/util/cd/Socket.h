#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace cd {

void connect(Socket* sock, const String& name, int port, int timeout);
void writeSocket(Socket* sock, const String& request);
string readSocket(Socket* sock, int timeout);

}  // namespace cd
}  // namespace util
}  // namespace rec

