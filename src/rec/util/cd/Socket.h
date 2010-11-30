#ifndef __REC_UTIL_CD_SOCKET__
#define __REC_UTIL_CD_SOCKET__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace cd {

void connect(Socket* sock, const String& name, int port, int timeout);
void writeSocket(Socket* sock, const String& request);
void readSocket(Socket* sock, String* out, int timeout);

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_SOCKET__
