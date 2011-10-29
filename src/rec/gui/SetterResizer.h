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
  typedef data::Editable Editable;

  SetterResizer(const data::Address& address,
                Layout* layout,
                int itemIndexInLayout,
                Editable* editable);

  int get() const;
  void set(int distance);
  void add(int size = 7);
  virtual void moved();
  virtual void paint(Graphics& g);
  virtual void setActive(bool a) { active_ = a; }

 private:
  Orientation orientation();
  void doSet(int distance);

  Layout* layout_;
  juce::StretchableLayoutManager* layoutManager_;
  int index_;
  data::Address address_;
  Editable* editable_;
  bool active_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
