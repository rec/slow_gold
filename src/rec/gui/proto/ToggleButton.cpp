#include "rec/gui/proto/ToggleButton.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeToggleButton(const ComponentProto& comp,
                                       const Constants&) {
  return unique_ptr<Component>(
      new SetterToggle(comp.name(), comp.tooltip(), comp.address()));
}


}  // namespace gui
}  // namespace rec
