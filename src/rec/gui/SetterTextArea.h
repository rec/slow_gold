#ifndef __REC_GUI_SETTERTEXTAREA__
#define __REC_GUI_SETTERTEXTAREA__

#include "rec/gui/layout/Layout.h"
#include "rec/gui/SetterText.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterTextArea : public Layout {
 public:
  SetterTextArea(const String& name = String::empty) : Layout(name, VERTICAL) {}

  ~SetterTextArea() { stl::deletePointers(&components_); }

  SetterText<Proto>* text(int i) {
    return static_cast<SetterText<Proto>*>(components_[i]);
  }

  SetterText<Proto>* add(const String& name,
                         const data::Address& addr,
                         const String& tip = String::empty,
                         const String& caption = String::empty) {
    SetterText<Proto>* text = new SetterText<Proto>(name, addr, tip, caption);
    addToLayout(text, 12, 20, 20);
    return text;
  }

  virtual void repaint() {  // TODO: remove this?
    Layout::repaint();
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SetterTextArea);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXTAREA__
