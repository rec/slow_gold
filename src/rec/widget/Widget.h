#ifndef __REC_WIDGET_WIDGET__
#define __REC_WIDGET_WIDGET__

#include "rec/base/base.h"
#include "rec/widget/Widget.pb.h"
#include "rec/gui/Color.h"
#include "rec/gui/Font.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {

template <typename Proto>
class WidgetBase {
 public:
  // TODO: move this enum to Color.proto.
  enum ColorNames {
    BACKGROUND,
    FOREGROUND,
    HIGHLIGHT,
  };

  WidgetBase(const Proto& desc) : desc_(desc) {}

  juce::Font startPaint(juce::Graphics& g) {
    const Widget& widget = desc_.widget();
    if (!widget.transparent())
      g.fillAll(colour(BACKGROUND));

    setColour(g, FOREGROUND);

    juce::Font f = g.getCurrentFont();
    if (widget.has_font())
      g.setFont(font());

    return f;
  }

  const juce::Font font() const { return gui::getFont(desc_.widget().font()); }
  const gui::Colors colors() const { return desc_.widget().colors(); }
  const juce::Colour colour(int i) const { return gui::color::get(colors(), i); }
  void setColor(juce::Graphics& g, int i) const { g.setColour(colour(i)); }
  void setColor(juce::Graphics& g, ColorNames n) const { setColor(g, (int)n); }

 protected:
  Proto desc_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(WidgetBase);
};

}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WIDGET__
