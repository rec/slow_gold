#include "rec/gui/proto/ToggleButton.h"
#include "rec/base/make_unique.h"

namespace rec {
namespace gui {

unique_ptr<SetterToggle> makeToggleButton(const ToggleButtonProto& proto) {
  return make_unique<SetterToggle>(proto.name(), proto.tooltip(),
                                   proto.data_address().type_name(),
                                   proto.data_address().address());

}


}  // namespace gui
}  // namespace rec
