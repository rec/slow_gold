#include "rec/gui/proto/Button.h"

#include "rec/data/AddressListener.h"
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
  DCHECK(drawable->get()) << "Couldn't create " << name;
}

class ModalButton : public LanguageButton, public data::AddressListener,
                    public juce::ButtonListener {
 public:
  ModalButton(const string& name,
              const string& tooltip,
              DrawableButton::ButtonStyle style,
              const data::Address& address,
              uint32 modeIndex)
      : LanguageButton(name, tooltip, style),
        AddressListener(address),
        modeIndex_(modeIndex) {
    addListener(this);
  }

  void operator()(const data::Value& value) override {
    setToggleState(value.enum_f() == modeIndex_, juce::dontSendNotification);
  }

  void buttonClicked(Button*) {
    value_.set_enum_f(modeIndex_);
    setValue(value_);
  }

 private:
  uint32 const modeIndex_;
  data::Value value_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ModalButton);
};

}  // namespace

unique_ptr<Component> makeButton(const Context& context) {
  auto& component = context.component_;
  const ButtonProto& proto = component.button();
  auto style = static_cast<DrawableButton::ButtonStyle>(proto.style());
  unique_ptr<LanguageButton> button(
      (proto.behavior() == ButtonProto::MODE) ?
      new ModalButton(component.name(), component.tooltip(), style,
                      data::splitAddress(component.address()),
                      proto.mode_index()) :
      new LanguageButton(component.name(), component.tooltip(), style));
  button->setTooltip(component.tooltip());

  bool isClick = (proto.behavior() == ButtonProto::CLICK);
  bool isMode = (proto.behavior() == ButtonProto::MODE);
  bool isToggle = (proto.behavior() == ButtonProto::TOGGLE);

  const string& imageName = component.name();
  const ButtonProto::State& state = proto.state();
  unique_ptr<Drawable> normal, over, pressed, disabled;
  construct(&normal, imageName);

  if (state.over())
    construct(&over, imageName + "Over");

  if (isClick or state.pressed())
    construct(&pressed, imageName + "Pressed");

  if (state.disabled())
    construct(&disabled, imageName + "Disabled");

  const ButtonProto::State& stateOn = proto.state_on();
  unique_ptr<Drawable> normalOn, overOn, pressedOn, disabledOn;
  if (isToggle or stateOn.normal())
    construct(&normalOn, imageName + "On");

  if (stateOn.over())
    construct(&overOn, imageName + "OnOver");

  if (stateOn.pressed())
    construct(&pressedOn, imageName + "OnPressed");

  if (stateOn.disabled())
    construct(&disabledOn, imageName + "OnDisabled");

  button->setImages(
      normal.get(), over.get(), pressed.get(), disabled.get(),
      normalOn.get(), overOn.get(), pressedOn.get(), disabledOn.get());

  if (not isMode) {
    button->setCommandToTrigger(
        program::applicationCommandManager(),
        program::getProgram()->nameToId(proto.command()) + proto.command_index(),
        not component.has_tooltip());
  }

  return unique_ptr<Component>(button.release());
}

}  // namespace gui
}  // namespace rec
