#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/data/persist/Persist.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/gui/Layout.h"

namespace rec {
namespace gui {

class SetterResizer : public StretchableLayoutResizerBar {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Setter Setter;

  SetterResizer(const Address& address,
                Layout* layout,
                int itemIndexInLayout);

  int get() const;
  void set(int distance);
  void setSetter(persist::Setter* setter);
  void add(int size = 7) {
    layout_->addToLayout(this, size, size, size);
  }
  virtual void moved();
  virtual void paint(Graphics& g);

 private:
  Layout* layout_;
  juce::StretchableLayoutManager* layoutManager_;
  int index_;
  Address address_;
  Orientation orientation_;
  Setter* setter_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
