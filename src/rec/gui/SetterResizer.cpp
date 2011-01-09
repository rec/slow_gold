#include "rec/gui/SetterResizer.h"

namespace rec {
namespace gui {

SetterResizer::SetterResizer(const Address& address,
                             juce::StretchableLayoutManager* layout,
                             int itemIndexInLayout,
                             Orientation o)
    : StretchableLayoutResizerBar(layout, itemIndexInLayout, o != HORIZONTAL),
      layout_(layout),
      index_(itemIndexInLayout),
      address_(address),
      orientation_(o),
      setter_(NULL) {
}

int SetterResizer::get() const {
  return (orientation_ == HORIZONTAL) ? getY() : getX();
}

void SetterResizer::set(int distance) {
  layout_->setItemPosition(index_, distance);
  hasBeenMoved();
}

void SetterResizer::setSetter(persist::Setter* setter) {
  setter_ = setter;
  int size = setter_->get(address_).uint32_f();
  thread::callAsync(this, &SetterResizer::set, size);
}

void SetterResizer::moved() {
  if (setter_)
    setter_->set(address_, static_cast<uint32>(get()));
}

void SetterResizer::paint(Graphics& g) {
  g.fillAll(juce::Colour(0xffDDDDF8));
  //g.fillAll(juce::Colour(0xffB0C0F0));
  StretchableLayoutResizerBar::paint(g);
}

}  // namespace gui
}  // namespace rec

