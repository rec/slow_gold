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
                Orientation o);

  int get() const;
  void set(int distance);
  void setSetter(persist::Setter* setter);
  virtual void moved();
  virtual void paint(Graphics& g);

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
