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

void SetterResizer::set(int distance) {
  doSet(distance);
  DLOG(INFO) << "SetterResizer::set";
  hasBeenMoved();
}

void SetterResizer::doSet(int distance) {
  MessageManagerLock l;
  layout_->layoutManager()->setItemPosition(index_, distance);
}

//  doSet(setter->getValue(address_).uint32_f());

void SetterResizer::moved() {
  if (active_)
    editable_->set(static_cast<uint32>(get()), address_);
}

void SetterResizer::add(int size) {
  layout_->addToLayout(this, size, size, size);
  data::Value value = editable_->getValue(address_);
  if (value.has_uint32_f())
    layout_->layoutManager()->setItemPosition(index_, value.uint32_f());
  else
    LOG(ERROR) << "No value ";
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  //g.fillAll(juce::Colour(0xffB0C0F0));
  StretchableLayoutResizerBar::paint(g);
}

}  // namespace gui
}  // namespace rec

