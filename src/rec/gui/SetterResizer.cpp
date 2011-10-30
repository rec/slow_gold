#include "rec/gui/SetterResizer.h"
#include "rec/data/Value.h"

namespace rec {
namespace gui {

SetterResizer::SetterResizer(const data::Address& address,
                             Layout* layout,
                             int itemIndexInLayout,
                             Editable* editable)
  : StretchableLayoutResizerBar(layout->layoutManager(),
                                itemIndexInLayout,
                                layout->orientation() == HORIZONTAL),
    layout_(layout),
    index_(itemIndexInLayout),
    address_(address),
    editable_(editable),
    active_(false) {
  DCHECK(editable);
}

int SetterResizer::get() const {
  return (layout_->orientation() == VERTICAL) ? getY() : getX();
}

void SetterResizer::doSet(int distance) {
  MessageManagerLock l;
  layout_->layoutManager()->setItemPosition(index_, distance);
}

void SetterResizer::moved() {
  if (active_)
    editable_->set(static_cast<uint32>(get()), address_);
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  StretchableLayoutResizerBar::paint(g);
}

void SetterResizer::setActive(bool a) {
  active_ = a;
  if (active_) {
    doSet(editable_->getValue(address_).uint32_f());
    MessageManagerLock l;
    hasBeenMoved();
  }
}

}  // namespace gui
}  // namespace rec

