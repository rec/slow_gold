#include "rec/gui/proto/ComboBox.h"

#include "rec/data/AddressListener.h"
#include "rec/data/Value.h"
#include "rec/gui/DisableableComponent.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

using namespace juce;
using namespace rec::data;

namespace rec {
namespace gui {

namespace {

class ComboBoxSetter : public AddressListener,
                       public ComboBox,
                       public ComboBox::Listener,
                       public DisableableComponent {
 public:
  explicit ComboBoxSetter(const Context& context)
      : AddressListener(data::splitAddress(context.component_.address())) {
    auto& component = context.component_;
    auto& combo = component.combo_box();
    setEditableText(false);
    setJustificationType(Justification::centredLeft);

    setTooltip(component.tooltip());

    for (int i = 0; i < combo.item_size(); ++i)
      addItem(combo.item(i), i + 1);

    setTextWhenNothingSelected(combo.item(0));
    setTextWhenNoChoicesAvailable(combo.item(0));
    addListener(this);
  }

  void operator()(const data::Value& v) override {
    setSelectedId(v.enum_f() + 1, juce::dontSendNotification);
  }

  void comboBoxChanged(ComboBox*) override {
    if (int id = getSelectedId()) {
      value_.set_enum_f(id - 1);
      setValue(value_);
    }
  }

 private:
  data::Value value_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ComboBoxSetter);
};

}  // namespace


unique_ptr<Component> makeComboBox(const Context& context) {
  return unique_ptr<Component>(new ComboBoxSetter(context));
}

}  // namespace gui
}  // namespace rec
