#include "rec/gui/proto/ComboBox.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<Component> makeComboBox(const ComponentProto& component,
                                   const Constants& constants) {
  auto& combo = component.combo_box();
  unique_ptr<ComboBox> comboBox(new ComboBox);
  comboBox->setEditableText(false);
  comboBox->setJustificationType(Justification::centredLeft);

  comboBox->setTooltip(component.tooltip());

  for (int i = 0; i < combo.item_size(); ++i)
    comboBox->addItem(combo.item(i), i);

  comboBox->setTextWhenNothingSelected(combo.item(0));
  comboBox->setTextWhenNoChoicesAvailable(combo.item(0));

  return unique_ptr<Component>(comboBox.release());
}

}  // namespace gui
}  // namespace rec
