#ifdef __APPLE__

#include "ews/EWSEmbedded.h"
#include "rec/util/ews/EWS.h"

namespace rec {
namespace util {
namespace ews {

bool isSystemCompatible() {
  return eWeb_IsSystemCompatible();
}

int attemptPurchase() {
  if (not isSystemCompatible())
    return -1;
#if 0
  char* resultData;
  const char* empty = nullptr;
  auto status = eWeb_Purchase(
      "STR6720703889",
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      &resultData);
#else
  auto status = eWeb_SilentCheckForUpdate(
      "STR6720703889",
      "SKU93916642620",
      nullptr,
      false,
      nullptr);
#endif

  return status;
}


}  // namespace ews
}  // namespace util
}  // namespace rec

#endif
