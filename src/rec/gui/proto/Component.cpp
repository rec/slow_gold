#include "rec/gui/proto/Component.h"

#include "rec/gui/proto/Button.h"
#include "rec/gui/proto/ComboBox.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"
#include "rec/gui/proto/Help.h"
#include "rec/gui/proto/Label.h"
#include "rec/gui/proto/Layout.h"
#include "rec/gui/proto/LevelMeter.h"
#include "rec/gui/proto/Panel.h"
#include "rec/gui/proto/Resizer.h"
#include "rec/gui/proto/Slider.h"
#include "rec/gui/proto/Text.h"
#include "rec/gui/proto/Time.h"
#include "rec/gui/proto/TimeDial.h"
#include "rec/gui/proto/ToggleButton.h"

namespace rec {
namespace gui {

namespace {

typedef unique_ptr<Component> (*ComponentMaker)(const Context&);

ComponentMaker make(const ComponentProto& c) {
  if (c.has_layout())
    return &makeLayoutComp;

  if (c.has_button())
    return &makeButton;

  if (c.has_combo_box())
    return &makeComboBox;

  if (c.has_help())
    return &makeHelp;

  if (c.has_label())
    return &makeLabel;

  if (c.has_level_meter())
    return &makeLevelMeter;

  if (c.has_resizer())
    return &makeSimpleResizer;

  if (c.has_full_resizer())
    return &makeResizer;

  if (c.has_slider())
    return &makeSlider;

  if (c.has_text())
    return &makeText;

  if (c.has_time())
    return &makeTime;

  if (c.has_time_dial())
    return &makeTimeDial;

  if (c.has_toggle_button())
    return &makeToggleButton;

  return nullptr;
}

}  // namespace

unique_ptr<Component> makeComponent(const Context& context) {
  auto& comp = context.component_;
  unique_ptr<Component> component;
  if (ComponentMaker maker = make(comp)) {
    component = maker(context);
    component->setName(comp.name());
    typedef SettableTooltipClient TTClient;
    if (TTClient* tt = dynamic_cast<TTClient*>(component.get()))
      tt->setTooltip(comp.tooltip());
  } else {
    LOG(DFATAL) << "No component in " << comp.ShortDebugString();
  }

  return std::move(component);
}

}  // namespace gui
}  // namespace rec
