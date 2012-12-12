#ifndef __REC_GUI_SETTERTEXTAREA__
#define __REC_GUI_SETTERTEXTAREA__

#include "rec/gui/layout/Layout.h"
#include "rec/gui/SetterText.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

class SetterTextArea : public Layout {
 public:
  SetterTextArea(const String& name = String::empty) : Layout(name, VERTICAL) {}
  ~SetterTextArea() { stl::deletePointers(&components_); }

  SetterText* text(int i) {
    return static_cast<SetterText*>(components_[i]);
  }

  SetterText* add(const String& name,
                  const string& typeName,
                  const data::Address& addr,
                  const String& tip = String::empty,
                  const String& caption = String::empty) {
    SetterText* text = new SetterText(name, typeName, addr, tip, caption);
    addToLayout(text, 12, 20, 20);
    return text;
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SetterTextArea);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXTAREA__
