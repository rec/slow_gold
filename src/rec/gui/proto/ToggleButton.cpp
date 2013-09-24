#include "rec/gui/proto/ToggleButton.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeToggleButton(const Context& context) {
  auto& comp = context.component_;
  return unique_ptr<Component>(
      new SetterToggle(comp.name(), comp.tooltip(),
                       data::splitAddress(comp.address())));
}


}  // namespace gui
}  // namespace rec
