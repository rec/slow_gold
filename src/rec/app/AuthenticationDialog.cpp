#include "rec/app/AuthenticationDialog.h"
#include "rec/data/Opener.h"
#include "rec/util/ews/Activation.pb.h"

namespace rec {
namespace app {

bool authenticate() {
  data::Opener<ews::Activation> activation(data::CANT_UNDO);
  return true;
}

}  // namespace app
}  // namespace rec
