#include "rec/gui/proto/Component.h"

#include "rec/gui/proto/Button.h"
#include "rec/gui/proto/ComboBox.h"
#include "rec/gui/proto/Label.h"
#include "rec/gui/proto/Panel.h"
#include "rec/gui/proto/Resizer.h"
#include "rec/gui/proto/Slider.h"
#include "rec/gui/proto/ToggleButton.h"

namespace rec {
namespace gui {

namespace {

Component* make(const ComponentProto& c,
                const Constants& constants) {
  if (c.has_button())
    return makeButton(c.button(), constants).release();

  if (c.has_combo_box())
    return makeComboBox(c.combo_box(), constants).release();

  if (c.has_label())
    return makeLabel(c.label(), constants).release();
/*
  if (c.has_panel())
    return makePanel(c.panel(), constants).release();
*/
  if (c.has_resizer())
    return makeResizer(c.resizer(), constants).release();

  if (c.has_slider())
    return makeSlider(c.slider(), constants).release();

  if (c.has_toggle_button())
    return makeToggleButton(c.toggle_button(), constants).release();

  return nullptr;
}

}  // namespace

unique_ptr<Component> makeComponent(const ComponentProto& proto,
                                    const Constants& constants) {
  return unique_ptr<Component>(make(proto, constants));
}

}  // namespace gui
}  // namespace rec
