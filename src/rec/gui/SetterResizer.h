#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/gui/GuiWriteable.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {

namespace data { class Data; }

namespace gui {

class SetterResizer : public StretchableLayoutResizerBar,
                      public SettableTooltipClient,
                      public data::GlobalAddressListener,
                      public GuiWriteable {
 public:
  SetterResizer(const string& typeName,
                const data::Address& address,
                Layout* layout,
                int itemIndexInLayout);

  virtual void operator()(const data::Value&);
  virtual void moved();
  virtual void paint(Graphics& g);

 protected:
  virtual void doWriteGui();
  uint32 get() const;

 private:
  Layout* layout_;
  juce::StretchableLayoutManager* layoutManager_;
  int index_;
  data::Address address_;
  bool active_;
  bool needsWrite_;
  uint32 lastValue_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterResizer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERRESIZER__
