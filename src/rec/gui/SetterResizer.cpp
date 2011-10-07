#include "rec/gui/SetterResizer.h"
#include "rec/data/Value.h"

namespace rec {
namespace gui {

SetterResizer::SetterResizer(const Address& address,
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
  layout_->layoutManager()->setItemPosition(index_, distance);
  hasBeenMoved();
}

void SetterResizer::setSetter(data::EditableData* setter) {
  setter_ = setter;
  int size = setter_->getValue(address_).uint32_f();
  thread::callAsync(this, &SetterResizer::set, size);
}

void SetterResizer::moved() {
  if (setter_)
    data::set(setter_, address_, static_cast<uint32>(get()));
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  //g.fillAll(juce::Colour(0xffB0C0F0));
  StretchableLayoutResizerBar::paint(g);
}

}  // namespace gui
}  // namespace rec

