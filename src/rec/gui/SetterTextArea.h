#ifndef __REC_GUI_SETTERTEXTAREA__
#define __REC_GUI_SETTERTEXTAREA__

#include "rec/gui/Layout.h"
#include "rec/gui/SetterText.h"
#include "rec/util/listener/ProtoListener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

class SetterTextArea : public Layout {
 public:
  typedef persist::UntypedData UntypedData;
  typedef proto::arg::Address Address;

  SetterTextArea(const String& name = String::empty)
      : Layout(name, VERTICAL) {
  }

  ~SetterTextArea() { stl::deletePointers(&components_); }

  SetterText* text(int i) { return static_cast<SetterText*>(components_[i]); }

  SetterText* add(const String& name, const Address& address,
                  const String& tip = String::empty,
                  const String& caption = String::empty) {
    SetterText* text = new SetterText(name, address, tip, caption);
    addToLayout(text, 12, 20, 20);
    return text;
  }

  void setData(UntypedData* data) {
    for (int i = 0; i < components_.size(); ++i)
      text(i)->setData(data);

#ifdef TODO
    if (data)
      data->requestUpdate();
#endif

  }

  void repaint() {
    Layout::repaint();
  }


 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterTextArea);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXTAREA__
