#ifndef __REC_GUI_SETTERTEXTAREA__
#define __REC_GUI_SETTERTEXTAREA__

#include "rec/gui/proto/Panel.h"
#include "rec/gui/SetterText.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

class SetterTextArea : public Panel {
 public:
  SetterTextArea(const String& name = String::empty) : Panel(name, VERTICAL) {}
  ~SetterTextArea() { stl::deletePointers(&components_); }

  SetterText* text(int i) {
    return static_cast<SetterText*>(components_[i]);
  }

  SetterText* add(const String& name,
                  const data::Address& addr,
                  const String& tip = String::empty,
                  const String& caption = String::empty) {
    SetterText* text = new SetterText(name, addr, tip, caption);
    addToPanel(text, 12, 20, 20);
    return text;
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SetterTextArea);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXTAREA__
