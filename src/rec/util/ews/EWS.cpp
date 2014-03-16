#ifdef __APPLE__

#include "ews/EWSEmbedded.h"
#include "rec/util/ews/EWS.h"

namespace rec {
namespace util {
namespace ews {

bool isSystemCompatible() {
  return eWeb_IsSystemCompatible();
}

}  // namespace ews
}  // namespace util
}  // namespace rec

#endif
