#ifndef __REC_GUI_SETTERTEXTAREA__
#define __REC_GUI_SETTERTEXTAREA__

#include "rec/gui/layout/Layout.h"
#include "rec/gui/SetterText.h"
#include "rec/util/listener/ProtoListener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

class SetterTextArea : public Layout {
 public:
  SetterTextArea(const String& name = String::empty)
      : Layout(name, VERTICAL), untypedData_(NULL) {
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

  virtual void setUntypedData(data::UntypedData* data) {
    untypedData_ = data;
    int size = static_cast<int>(components_.size());
    for (int i = 0; i < size; ++i)
      text(i)->setUntypedData(data);
  }

  virtual void repaint() {  // TODO: remove this?
    Layout::repaint();
  }

 protected:
  data::UntypedData* untypedData_;

 private:
  DISALLOW_COPY_AND_ASSIGN(SetterTextArea);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTEXTAREA__
