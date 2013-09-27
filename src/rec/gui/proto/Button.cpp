#include "rec/gui/proto/Button.h"
#include "rec/gui/LanguageButton.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"
#include "rec/program/Program.h"
#include "rec/program/JuceModel.h"
#include "rec/util/Binary.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {

void construct(unique_ptr<Drawable>* drawable, const string& name) {
  drawable->reset(constructName<Drawable>(name + "_svg"));
}

}  // namespace

unique_ptr<Component> makeButton(const Context& context) {
  auto& component = context.component_;
  const ButtonProto& proto = component.button();
  auto style = static_cast<DrawableButton::ButtonStyle>(proto.style());
  unique_ptr<LanguageButton> button(
      new LanguageButton(component.name(), component.tooltip(), style));
  button->setTooltip(component.tooltip());

  bool isToggle = (proto.behavior() == ButtonProto::TOGGLE);

  const string& imageName = component.name();
  const ButtonProto::State& state = proto.state();
  unique_ptr<Drawable> normal, over, pressed, disabled;
  construct(&normal, imageName);

  if (state.over())
    construct(&over, imageName + "Over");

  if (not isToggle and (not proto.has_state() or state.pressed()))
    construct(&pressed, imageName + "Pressed");

  if (state.disabled())
    construct(&disabled, imageName + "Disabled");

  const ButtonProto::State& stateOn = proto.state_on();
  unique_ptr<Drawable> normalOn, overOn, pressedOn, disabledOn;
  if (isToggle or stateOn.normal())
    construct(&overOn, imageName + "On");

  if (stateOn.over())
    construct(&overOn, imageName + "OnOver");

  if (stateOn.pressed())
    construct(&pressedOn, imageName + "OnPressed");

  if (stateOn.disabled())
    construct(&disabledOn, imageName + "OnDisabled");

  button->setImages(
      normal.get(), over.get(), pressed.get(), disabled.get(),
      normalOn.get(), overOn.get(), pressedOn.get(), disabledOn.get());

  button->setCommandToTrigger(
      program::applicationCommandManager(),
      program::getProgram()->nameToId(proto.command()) + proto.command_index(),
      not component.has_tooltip());

  return unique_ptr<Component>(button.release());
}

}  // namespace gui
}  // namespace rec
