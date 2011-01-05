#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class SetterResizer : public StretchableLayoutResizerBar {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  SetterResizer(const Address& address,
                juce::StretchableLayoutManager* slm,
                int itemIndexInLayout,
                Orientation o)
      : StretchableLayoutResizerBar(slm, itemIndexInLayout, o != HORIZONTAL),
        address_(address),
        orientation_(o),
        setter_(NULL) {
  }

  int get() const {
    return (orientation_ == HORIZONTAL) ? getHeight() : getWidth();
  }

  void set(int distance) {
    if (orientation_ == HORIZONTAL)
      setHeight(distance);
    else
      setWidth(distance);
  }

  void setSetter(Setter* setter) {
    setter_ = setter;
  }

  virtual void moved() {
    if (setter_)
      setter_->set(address_, get());
  }

 private:
  Address address_;
  Orientation orientation_;
  Setter* setter_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
