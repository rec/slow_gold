#ifndef __REC_WIDGET_WIDGET__
#define __REC_WIDGET_WIDGET__

#include "rec/base/base.h"
#include "rec/widget/Widget.pb.h"
#include "rec/gui/Color.h"
#include "rec/gui/Font.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {

class Painter {
 public:
  // TODO: move this enum to Color.proto.
  enum ColorNames {
    BACKGROUND,
    FOREGROUND,
    HIGHLIGHT,
  };

  Painter(const Widget& widget, juce::Graphics* g)
      : widget_(widget),
        graphics_(g),
        font_(g->getCurrentFont()),
        margin_(widget_.margin()) {
    if (!widget_.transparent())
      g->fillAll(colour(BACKGROUND));

    setColor(FOREGROUND);

    if (widget_.has_font())
      g->setFont(font());
  }

  ~Painter() { graphics_->setFont(font_); }

  const juce::Font font() const { return gui::getFont(widget_.font()); }

  const gui::Colors& colors() const { return widget_.colors(); }
  const juce::Colour colour(int i) const { return gui::color::get(colors(), i); }

  void setColor(int i) const { graphics_->setColour(colour(i)); }

  void setColor(ColorNames n) const { setColor((int)n); }

  juce::Rectangle<int> getBounds(juce::Component* c) const {
    return c->getLocalBounds().reduced(margin_, margin_);
  }

  int margin() const { return margin_; }


 private:
  const Widget& widget_;
  juce::Graphics* const graphics_;
  juce::Font const font_;
  int margin_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Painter);
};

}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WIDGET__
