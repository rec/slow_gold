#include "rec/gui/SetterResizer.h"

#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/Value.h"

namespace rec {
namespace gui {

SetterResizer::SetterResizer(const data::Address& address,
                             const string& typeName,
                             Layout* layout,
                             int itemIndexInLayout)
  : StretchableLayoutResizerBar(layout->layoutManager(),
                                itemIndexInLayout,
                                layout->orientation() == HORIZONTAL),
    data::GlobalAddressListener(address, typeName),
    layout_(layout),
    index_(itemIndexInLayout),
    address_(address) {
  DCHECK(data);
  setTooltip("You can drag this resizer around to change the screen layout.");
}

int SetterResizer::get() const {
  return (layout_->orientation() == VERTICAL) ? getY() : getX();
}

void SetterResizer::moved() {
  setValue(static_cast<uint32>(get()));
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  StretchableLayoutResizerBar::paint(g);
}

}  // namespace gui
}  // namespace rec

