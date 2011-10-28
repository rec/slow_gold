#include "rec/gui/SetterResizer.h"
#include "rec/data/Value.h"

namespace rec {
namespace gui {

SetterResizer::SetterResizer(const data::Address& address,
                             Layout* layout,
                             int itemIndexInLayout)
  : StretchableLayoutResizerBar(layout->layoutManager(),
                                itemIndexInLayout,
                                layout->orientation() == HORIZONTAL),
    layout_(layout),
    index_(itemIndexInLayout),
    address_(address),
    orientation_(inverse(layout->orientation())),
    setter_(NULL) {
}

int SetterResizer::get() const {
  return (orientation_ == HORIZONTAL) ? getY() : getX();
}

void SetterResizer::set(int distance) {
  doSet(distance);
  hasBeenMoved();
}

void SetterResizer::doSet(int distance) {
  MessageManagerLock l;
  layout_->layoutManager()->setItemPosition(index_, distance);
}

void SetterResizer::setSetter(data::Editable* setter) {
  setter_ = setter;
  doSet(setter_->getValue(address_).uint32_f());
}

void SetterResizer::moved() {
  if (setter_)
    setter_->set(static_cast<uint32>(get()), address_);
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  //g.fillAll(juce::Colour(0xffB0C0F0));
  StretchableLayoutResizerBar::paint(g);
}

}  // namespace gui
}  // namespace rec

