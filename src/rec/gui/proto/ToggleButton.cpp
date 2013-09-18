#include "rec/gui/proto/ToggleButton.h"
#include "rec/base/make_unique.h"

namespace rec {
namespace gui {

unique_ptr<SetterToggle> makeToggleButton(const ToggleButtonProto& proto,
                                          const Constants&) {
  return make_unique<SetterToggle>(proto.name(), proto.tooltip(),
                                   proto.address().type_name(),
                                   proto.address());

}


}  // namespace gui
}  // namespace rec
