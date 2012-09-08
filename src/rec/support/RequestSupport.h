#ifndef __REC_SUPPORT_REQUESTSUPPORT__
#define __REC_SUPPORT_REQUESTSUPPORT__

#include "rec/base/base.h"

namespace rec {
namespace support {

void requestSupport();

struct RequestSupport {
  static void registerAllTranslations();
};


}  // namespace support
}  // namespace rec

#endif  // __REC_SUPPORT_REQUESTSUPPORT__
