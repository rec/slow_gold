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
                             int itemIndexInLayout)
  : StretchableLayoutResizerBar(layout->layoutManager(),
                                itemIndexInLayout,
                                layout->orientation() == HORIZONTAL),
    data::GlobalAddressListener(address, typeName),
    layout_(layout),
    index_(itemIndexInLayout),
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
  requestWrite();
  DLOG(INFO) << "requestWrite " << address_.ShortDebugString();
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  StretchableLayoutResizerBar::paint(g);
}

void SetterResizer::operator()(const data::Value& v) {
  uint32 coord = v.uint32_f();
  DLOG(INFO) << "Got an update! " << coord << ", |" << v.ShortDebugString() << "|";
  MessageManagerLock l;
  if (coord && coord != get()) {
    if (layout_->orientation() == VERTICAL)
      setTopLeftPosition(getX(), coord);
    else
      setTopLeftPosition(coord, getY());
  }
}

void SetterResizer::doWriteGui() {
  Lock l(lock_);
  uint32 val = get();
  if (lastValue_ != val) {
    DLOG(INFO) << "doWriteGui " << lastValue_ << ", " << val;
    setValue(val);
    lastValue_ = val;
  } else {
    DLOG(INFO) << "doWriteGui NO: " << val;
  }
}

}  // namespace gui
}  // namespace rec

