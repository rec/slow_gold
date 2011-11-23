#ifndef __REC_WIDGET_PAINTER__
#define __REC_WIDGET_PAINTER__

#include "rec/widget/Widget.h"
#include "rec/gui/Color.h"
#include "rec/gui/Font.h"

namespace rec {
namespace widget {

enum ColorName {
  BACKGROUND,
  FOREGROUND,
  HIGHLIGHT,
  BORDER,
  MIDGROUND,
  SPECIAL,
  BLACK,
  REGULAR,
};

class Painter {
 public:
  // TODO: move this enum to Color.proto.
  Painter(const Widget& widget, juce::Graphics* g,
          const StateColors* stateColors = NULL)
      : widget_(widget),
        graphics_(g),
        font_(g->getCurrentFont()),
        margin_(widget_.margin()),
        colors_(getColors(widget.state(), stateColors, widget.colors())) {
    if (!widget_.transparent())
      g->fillAll(colour(BACKGROUND));

    setColor(FOREGROUND);
    g->setFont(font());
  }

  ~Painter() { graphics_->setFont(font_); }

  const Font font() const { return gui::getFont(widget_.font()); }
  Graphics* graphics() { return graphics_; }

  const gui::Colors& colors() const { return colors_; }
  const Colour colour(int i) const { return gui::color::get(colors_, i); }
  void fillAll(ColorName n) { graphics_->fillAll(colour(n)); }

  void setColor(int i) const { graphics_->setColour(colour(i)); }

  void setColor(ColorName n) const { setColor((int)n); }

  juce::Rectangle<int> getBounds(juce::Component* c) const {
    return c->getLocalBounds().reduced(margin_, margin_);
  }

  int margin() const { return margin_; }

 private:
  const Widget& widget_;
  juce::Graphics* const graphics_;
  juce::Font const font_;
  int margin_;
  const Colors& colors_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Painter);
};

}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_PAINTER__
