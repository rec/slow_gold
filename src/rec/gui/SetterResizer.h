#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {

namespace data { class Data; }

namespace gui {

class SetterResizer : public StretchableLayoutResizerBar,
                      public SettableTooltipClient,
                      public data::AddressListener {
 public:
  SetterResizer(const string& typeName,
                const data::Address& address,
                Layout* layout,
                int itemIndexInLayout,
                Scope scope = FILE_SCOPE);

  virtual void operator()(const data::Value&);
  int get() const;
  virtual void moved();
  virtual void paint(Graphics& g);

 private:
  Layout* layout_;
  juce::StretchableLayoutManager* layoutManager_;
  int index_;
  data::Address address_;
  bool active_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
