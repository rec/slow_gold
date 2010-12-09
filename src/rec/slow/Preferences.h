#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/slow/Preferences.pb.h"
#include "rec/data/persist/Data.h"
#include "rec/audio/AudioDeviceSetup.h"

namespace rec {
namespace slow {

typedef persist::Data<proto::Preferences> Data;
typedef persist::Data<audio::AudioDeviceSetupProto> AudioSetupData;

Data* prefs();
const proto::Preferences getPreferences();

AudioSetupData* audioSetupData();

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
