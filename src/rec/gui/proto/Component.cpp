#include "rec/gui/proto/Component.h"

#include "rec/gui/proto/Button.h"
#include "rec/gui/proto/ComboBox.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Help.h"
#include "rec/gui/proto/Label.h"
#include "rec/gui/proto/Panel.h"
#include "rec/gui/proto/Resizer.h"
#include "rec/gui/proto/Slider.h"
#include "rec/gui/proto/ToggleButton.h"

namespace rec {
namespace gui {

namespace {

typedef unique_ptr<Component> (*ComponentMaker)(
    const ComponentProto&, const Constants&);

ComponentMaker make(const ComponentProto& c) {
  if (c.has_button())
    return &makeButton;

  if (c.has_combo_box())
    return &makeComboBox;

  if (c.has_help())
    return &makeHelp;

  if (c.has_label())
    return &makeLabel;
/*
   TODO: resizers go here.
*/
  if (c.has_full_resizer())
    return &makeResizer;

  if (c.has_slider())
    return &makeSlider;

  if (c.has_toggle_button())
    return &makeToggleButton;

  return nullptr;
}

}  // namespace

unique_ptr<Component> makeComponent(const ComponentProto& proto,
                                    const Constants& constants) {
  unique_ptr<Component> component;
  if (ComponentMaker maker = make(proto))
    component = maker(proto, constants);

  component->setName(proto.name());
  typedef SettableTooltipClient TTClient;
  if (TTClient* tt = dynamic_cast<TTClient*>(component.get()))
    tt->setTooltip(proto.tooltip());

  return std::move(component);
}

}  // namespace gui
}  // namespace rec
