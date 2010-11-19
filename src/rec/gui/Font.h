#ifndef __REC_GUI_FONT__
#define __REC_GUI_FONT__

#include "rec/base/base.h"
#include "rec/gui/Font.pb.h"

namespace rec {
namespace gui {

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
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_FONT__
