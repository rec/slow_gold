#ifndef __REC_WIDGETS_WIDGET__
#define __REC_WIDGETS_WIDGET__

#include "rec/base/base.h"
#include "rec/widgets/Widget.pb.h"
#include "rec/gui/Color.h"
#include "rec/gui/Font.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widgets {

template <typename Parent>
class WidgetBase : public Parent {
 public:
  WidgetBase(const WidgetDesc& desc) : Parent(desc.name().c_str()), desc_(desc) {}

  virtual void paint(Graphics& g) {
    if (!desc_.transparent())
      g.fillAll(gui::color::get(desc_.colors(), 0));

    g.setColour(gui::color::get(desc_.colors(), 1));

    Font font = g.getCurrentFont();
    if (desc_.has_font())
      g.setFont(gui::getFont(desc_.font()));

    uint32 margin = desc_.margin();
    doPaint(g, this->getBounds().reduced(margin, margin));

    if (desc_.has_font())
      g.setFont(font);
  }
  
  virtual void doPaint(Graphics& g, const Rectangle<int>& bounds) = 0;

 private:
  WidgetDesc desc_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(WidgetBase);

};

}  // namespace widgets
}  // namespace rec

#endif  // __REC_WIDGETS_WIDGET__
