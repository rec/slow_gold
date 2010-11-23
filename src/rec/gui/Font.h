#ifndef __REC_GUI_FONT__
#define __REC_GUI_FONT__

#include "rec/base/base.h"
#include "rec/gui/Font.pb.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {

static const int FONT_SIZE = 14;

inline const juce::Font getDefaultFont() {
  return juce::Font(juce::Font::getDefaultMonospacedFontName(), FONT_SIZE,
                    juce::Font::plain);
}

inline const juce::Font getFont(const FontDesc& font) {
  using juce::Font;
  int style = 0;

  if (font.has_style()) {
    const FontDesc::Style &s = font.style();
    if (s.has_bold())
      style += Font::bold;

    if (s.has_italic())
      style += Font::italic;

    if (s.has_underlined())
      style += Font::underlined;
  }

  String name;
  if (font.has_name())
    name = font.name().c_str();

  else if (font.type() == FontDesc::SANS_SERIF)
    name = juce::Font::getDefaultSansSerifFontName();

  else if (font.type() == FontDesc::SERIF)
    name = juce::Font::getDefaultSerifFontName();

  else if (font.type() == FontDesc::MONOSPACE)
    name = juce::Font::getDefaultMonospacedFontName();

  else
    return Font(font.font_height(), style);

  return Font(name, font.font_height(), style);
}

inline const juce::Font getFont(const FontDesc* font) {
  return font ? getFont(*font) : getDefaultFont();
};

template <typename Proto>
juce::Font getFont(const Proto& proto) {
  return getFont(proto.has_font() ? &proto.font() : NULL);
}

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_FONT__
