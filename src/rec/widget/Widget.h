#ifndef __REC_WIDGET_WIDGET__
#define __REC_WIDGET_WIDGET__

#include "rec/base/base.h"
#include "rec/widget/Widget.pb.h"
#include "rec/gui/Color.h"
#include "rec/gui/Font.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {

template <typename Parent, typename Proto>
class WidgetBase : public Parent {
 public:
  enum ColorNames {
    BACKGROUND,
    FOREGROUND,
    HIGHLIGHT,
  };

  WidgetBase(const Proto& desc)
      : Parent(desc.widget().name().c_str()), desc_(desc) {
  }

  virtual void paint(Graphics& g) {
    const Widget& widget = desc_.widget();
    if (!widget.transparent())
      g.fillAll(colour(BACKGROUND));

    setColour(g, FOREGROUND);

    Font f = g.getCurrentFont();
    if (widget.has_font())
      g.setFont(font());

    uint32 margin = widget.margin();
    paint(g, this->getLocalBounds().reduced(margin, margin));

    if (widget.has_font())
      g.setFont(f);
  }

  virtual void paint(Graphics& g, const Rectangle<int>& bounds) = 0;

  const Font font() const { return gui::getFont(desc_.widget().font()); }
  const gui::Colors colors() const { return desc_.widget().colors(); }
  const Colour colour(int i) const { return gui::color::get(colors(), i); }
  void setColour(Graphics& g, int i) const { g.setColour(colour(i)); }

 protected:
  Proto desc_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(WidgetBase);
};

}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WIDGET__
