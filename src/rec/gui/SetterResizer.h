#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/data/Data.h"
#include "rec/data/Address.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/gui/layout/Layout.h"

namespace rec {
namespace gui {

class SetterResizer : public StretchableLayoutResizerBar {
 public:
  SetterResizer(const data::Address& address,
                Layout* layout,
                int itemIndexInLayout,
                data::Editable* editable);

  int get() const;
  virtual void moved();
  virtual void paint(Graphics& g);

 private:
  Layout* layout_;
  juce::StretchableLayoutManager* layoutManager_;
  int index_;
  data::Address address_;
  data::Editable* editable_;
  bool active_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
