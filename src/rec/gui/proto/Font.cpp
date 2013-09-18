#include "rec/gui/proto/Font.h"

namespace rec {
namespace gui {

Font makeFont(const FontProto& f, float height) {
  if (f.has_height())
    height = f.height();
  height += f.height_delta();

  int flags = 0;
  if (f.is_bold())
    flags += Font::bold;
  if (f.is_italic())
    flags += Font::italic;
  if (f.is_underlined())
    flags += Font::underlined;

  Font font(height, flags);
  if (f.has_typeface_name())
    font.setTypefaceName(str(f.typeface_name()));

  if (f.has_typeface_style())
    font.setTypefaceStyle(str(f.typeface_style()));

  return font;
}

}  // namespace gui
}  // namespace rec
