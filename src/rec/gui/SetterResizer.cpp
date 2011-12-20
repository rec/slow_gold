#include "rec/gui/SetterResizer.h"

#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/Value.h"

namespace rec {
namespace gui {

SetterResizer::SetterResizer(const data::Address& address,
                             const string& typeName,
                             Layout* layout,
                             int itemIndexInLayout,
                             Scope scope)
  : StretchableLayoutResizerBar(layout->layoutManager(),
                                itemIndexInLayout,
                                layout->orientation() == HORIZONTAL),
    data::AddressListener(address, typeName, scope),
    layout_(layout),
    index_(itemIndexInLayout),
    address_(address) {
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

void SetterResizer::operator()(const data::Value& v) {
  int32 coord = v.int32_f();
  if (coord != get()) {
    if (layout_->orientation() == VERTICAL)
      setTopLeftPosition(getX(), coord);
    else
      setTopLeftPosition(coord, getY());
  }
}

}  // namespace gui
}  // namespace rec

