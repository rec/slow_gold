#include "rec/gui/SetterResizer.h"

#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/Value.h"

namespace rec {
namespace gui {

static uint32 NO_VALUE = static_cast<uint32>(-1);

SetterResizer::SetterResizer(const string& typeName,
                             const data::Address& address,
                             Layout* layout,
                             int itemIndexInLayout,
                             uint32 minValue)
  : StretchableLayoutResizerBar(layout->layoutManager(),
                                itemIndexInLayout,
                                layout->orientation() == HORIZONTAL),
    data::GlobalAddressListener(address, typeName),
    layout_(layout),
    index_(itemIndexInLayout),
    minValue_(minValue),
    address_(address),
    needsWrite_(false),
    lastValue_(NO_VALUE) {
  setTooltip("You can drag this resizer around to change the screen layout.");
  setWriteable(true);
}

uint32 SetterResizer::get() const {
  bool isVertical = (layout_->orientation() == VERTICAL);
  return static_cast<uint32>(isVertical ? getY() : getX());
}

void SetterResizer::moved() {
  Lock l(lock_);
  if (isStarted())
    requestWrite();
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  StretchableLayoutResizerBar::paint(g);
}

void SetterResizer::operator()(const data::Value& v) {
  uint32 coord = v.uint32_f();
  MessageManagerLock l;
  if (coord >= minValue_ && coord != get()) {
    if (layout_->orientation() == VERTICAL)
      setTopLeftPosition(getX(), coord);
    else
      setTopLeftPosition(coord, getY());
    layout_->layoutManager()->setItemPosition(index_, coord);
    hasBeenMoved();
  }
}

void SetterResizer::doWriteGui() {
  if (!isStarted())
    return;

  Lock l(lock_);
  uint32 val = get();
  if (lastValue_ != val && val >= minValue_) {
    setValue(val);
    lastValue_ = val;
  }
}

}  // namespace gui
}  // namespace rec

