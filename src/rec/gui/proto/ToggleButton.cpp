#include "rec/gui/proto/ToggleButton.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeToggleButton(const Context& context) {
  auto& comp = context.component_;

  unique_ptr<SetterToggle> st(
      new SetterToggle(comp.name(), comp.tooltip(), comp.address()));
  st->setButtonText(str(comp.toggle_button().caption()));
  return unique_ptr<Component>(st.release());
}


}  // namespace gui
}  // namespace rec
