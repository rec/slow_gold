#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/data/persist/Persist.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterResizer : public StretchableLayoutResizerBar {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Setter Setter;

  SetterResizer(const Address& address,
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

  int get() const {
    return (orientation_ == HORIZONTAL) ? getY() : getX();
  }

  void set(int distance) {
    layout_->setItemPosition(index_, distance);
    hasBeenMoved();
  }

  void setSetter(persist::Setter* setter) {
    setter_ = setter;
    int size = setter_->get(address_).uint32_f();
    thread::callAsync(this, &SetterResizer::set, size);
  }

  virtual void moved() {
    if (setter_)
      setter_->set(address_, static_cast<uint32>(get()));
  }

 private:
  juce::StretchableLayoutManager* layout_;
  int index_;
  Address address_;
  Orientation orientation_;
  Setter* setter_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
