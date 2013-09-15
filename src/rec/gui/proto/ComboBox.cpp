#include "rec/gui/proto/ComboBox.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<ComboBox> makeComboBox(const ComboBoxProto& combo) {
  unique_ptr<ComboBox> comboBox(new ComboBox);
  comboBox->setEditableText(false);
  comboBox->setJustificationType(Justification::centredLeft);

  comboBox->setTooltip(combo.tooltip());

  for (int i = 0; i < combo.item_size(); ++i)
    comboBox->addItem(combo.item(i), i);

  comboBox->setTextWhenNothingSelected(combo.item(0));
  comboBox->setTextWhenNoChoicesAvailable(combo.item(0));

  return std::move(comboBox);
}

}  // namespace gui
}  // namespace rec
