#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/data/persist/Persist.h"
#include "rec/data/Address.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/gui/layout/Layout.h"

namespace rec {
namespace gui {

class SetterResizer : public StretchableLayoutResizerBar {
 public:
  SetterResizer(const data::Address& address,
                Layout* layout,
                int itemIndexInLayout);

  int get() const;
  void set(int distance);
  void setSetter(data::Editable* setter);
  void add(int size = 7) {
    layout_->addToLayout(this, size, size, size);
  }
  virtual void moved();
  virtual void paint(Graphics& g);

 private:
  Layout* layout_;
  juce::StretchableLayoutManager* layoutManager_;
  int index_;
  data::Address address_;
  Orientation orientation_;
  data::Editable* setter_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
