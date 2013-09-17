#include "rec/gui/proto/Button.h"
#include "rec/util/Binary.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {

void construct(unique_ptr<Drawable>* drawable, const string& name) {
  drawable->reset(constructName<Drawable>(name + "_svg"));
}

}  // namespace

unique_ptr<LanguageButton> makeButton(const ButtonProto& proto) {
  auto style = static_cast<DrawableButton::ButtonStyle>(proto.style());
  unique_ptr<LanguageButton> button(
      new LanguageButton(proto.name(), proto.tooltip(), style));
  button->setTooltip(proto.tooltip());

  const string& imageName = proto.image_name();
  const ButtonProto::HasState& state = proto.state();
  unique_ptr<Drawable> normal, over, down, disabled;
  construct(&normal, imageName);

  if (state.over())
    construct(&over, imageName + "Over");

  if (state.down())
    construct(&down, imageName + "Down");

  if (state.disabled())
    construct(&disabled, imageName + "Disabled");

  const ButtonProto::HasState& stateOn = proto.state_on();
  unique_ptr<Drawable> normalOn, overOn, downOn, disabledOn;
  if (stateOn.normal())
    construct(&overOn, imageName + "OnOver");

  if (stateOn.over())
    construct(&overOn, imageName + "OnOver");

  if (stateOn.down())
    construct(&downOn, imageName + "OnDown");

  if (stateOn.disabled())
    construct(&disabledOn, imageName + "OnDisabled");

  button->setImages(
      normal.get(), over.get(), down.get(), disabled.get(),
      normalOn.get(), overOn.get(), downOn.get(), disabledOn.get());

  return std::move(button);
}

}  // namespace gui
}  // namespace rec
