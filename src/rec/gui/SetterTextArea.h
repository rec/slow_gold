#ifndef __REC_GUI_SETTERTEXTAREA__
#define __REC_GUI_SETTERTEXTAREA__

#include "rec/gui/Layout.h"
#include "rec/gui/SetterText.h"
#include "rec/util/listener/AddressListener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/STL.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterTextArea : public Layout,
                       public Reference<persist::Data<Proto> > {
 public:
  typedef SetterText<Proto> Text;
  typedef persist::Data<Proto> Data;
  typedef proto::arg::Address Address;

  SetterTextArea(const String& name = String::empty)
      : Layout(name, VERTICAL) {
  }

  ~SetterTextArea() { stl::deletePointers(&components_); }

  Text* text(int i) { return static_cast<Text*>(components_[i]); }

  Text* add(const String& name, const Address& address,
           const String& tip = String::empty,
           const String& caption = String::empty) {
    Text* text = new Text(name, address, tip, caption);
    addToLayout(text, 12, 20, 20);
    return text;
  }

  virtual void setData(Data* data) {
    Reference<persist::Data<Proto> >::setData(data);
    for (int i = 0; i < components_.size(); ++i)
      text(i)->setData(data);

    if (data)
      data->requestUpdate();
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
