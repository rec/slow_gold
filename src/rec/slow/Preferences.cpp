#include <google/protobuf/descriptor.h>

#include "rec/slow/Preferences.h"
#include "rec/data/persist/App.h"

namespace rec {
namespace slow {

Data* prefs() {
  static Data* prefs = persist::getApp()->
    getData<proto::Preferences>("preferences");
  return prefs;
}

const proto::Preferences getPreferences() {
  return prefs()->get();
}

}  // namespace slow
}  // namespace rec
