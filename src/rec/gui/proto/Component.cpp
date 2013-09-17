#include "rec/gui/proto/Component.h"

#include "rec/gui/proto/Button.h"
#include "rec/gui/proto/ComboBox.h"
#include "rec/gui/proto/Label.h"
#include "rec/gui/proto/Layout.h"
#include "rec/gui/proto/Resizer.h"
#include "rec/gui/proto/Slider.h"
#include "rec/gui/proto/ToggleButton.h"

namespace rec {
namespace gui {

namespace {

Component* make(const ComponentProto& c) {
  if (c.has_button())
    return makeButton(c.button()).release();

  if (c.has_combo_box())
    return makeComboBox(c.combo_box()).release();

  if (c.has_label())
    return makeLabel(c.label()).release();

  if (c.has_layout())
    return makeLayout(c.layout()).release();

  if (c.has_resizer())
    return makeResizer(c.resizer()).release();

  if (c.has_slider())
    return makeSlider(c.slider()).release();

  if (c.has_toggle_button())
    return makeToggleButton(c.toggle_button()).release();

  return nullptr;
}

}  // namespace

unique_ptr<Component> makeComponent(const ComponentProto& proto) {
  return unique_ptr<Component>(make(proto));
}

}  // namespace gui
}  // namespace rec
