#include "rec/gui/SetterResizer.h"

#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/Value.h"

namespace rec {
namespace gui {

SetterResizer::SetterResizer(const string& typeName,
                             const data::Address& address,
                             Layout* layout,
                             int itemIndexInLayout,
                             Scope scope)
  : StretchableLayoutResizerBar(layout->layoutManager(),
                                itemIndexInLayout,
                                layout->orientation() == HORIZONTAL),
    data::AddressListener(address, typeName, scope),
    layout_(layout),
    index_(itemIndexInLayout),
    address_(address),
    needsWrite_(false),
    lastValue_(-1) {
  setTooltip("You can drag this resizer around to change the screen layout.");
}

int SetterResizer::get() const {
  return (layout_->orientation() == VERTICAL) ? getY() : getX();
}

void SetterResizer::moved() {
  Lock l(lock_);
  lastValue_ = get();
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  StretchableLayoutResizerBar::paint(g);
}

void SetterResizer::operator()(const data::Value& v) {
  MessageManagerLock l;
  int32 coord = v.int32_f();
  if (coord && coord != get()) {
    if (layout_->orientation() == VERTICAL)
      setTopLeftPosition(getX(), coord);
    else
      setTopLeftPosition(coord, getY());
  }
}

void SetterResizer::doWriteGui() {
  Lock l(lock_);
  int val = static_cast<uint32>(get());
  if (lastValue_ != val)
    setValue((lastValue_ = val));
}

}  // namespace gui
}  // namespace rec

