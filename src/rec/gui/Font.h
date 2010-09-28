#ifndef __REC_GUI_FONT__
#define __REC_GUI_FONT__

#include "rec/base/basictypes.h"
#include "rec/gui/Font.pb.h"

namespace rec {
namespace gui {

inline const Font getFont(const FontDesc& font) {
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
  if (font.has_name())
    return Font(font.name().c_str(), font.font_height(), style);
  else
    return Font(font.font_height(), style);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_FONT__
