#ifndef __REC_GUI_SETTERRESIZER__
#define __REC_GUI_SETTERRESIZER__

#include "rec/app/LanguageListener.h"
#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/gui/GuiWriteable.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {

namespace data { class Data; }

namespace gui {

class SetterResizer : public data::AddressListener,
                      public app::LanguageListener,
                      public StretchableLayoutResizerBar,
                      public SettableTooltipClient,
                      public GuiWriteable {
 public:
  SetterResizer(const string& typeName,
                const data::Address& address,
                Layout* layout,
                int itemIndexInLayout,
                uint32 minValue = 20);

  virtual void operator()(const data::Value&);
  virtual void moved();
  virtual void paint(Graphics& g);
  virtual void languageChanged();

 protected:
  virtual void doWriteGui();
  uint32 get() const;

 private:
  Layout* const layout_;
  const int index_;
  const uint32 minValue_;

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
