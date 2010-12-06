#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/slow/Preferences.pb.h"
#include "rec/data/persist/Data.h"

namespace rec {
namespace slow {

typedef persist::Data<proto::Preferences> Data;

Data* prefs();
const proto::Preferences getPreferences();

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
