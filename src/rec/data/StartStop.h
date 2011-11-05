#ifndef __REC_DATA_STARTSTOP__
#define __REC_DATA_STARTSTOP__

#include "rec/base/base.h"

namespace rec {

namespace util { class DefaultRegistry; }

namespace data {

void start(DefaultRegistry* registry);
void stop();

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_STARTSTOP__
