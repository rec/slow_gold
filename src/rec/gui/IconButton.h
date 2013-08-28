#ifndef __REC_GUI_ICONBUTTON__
#define __REC_GUI_ICONBUTTON__

#include "rec/util/Binary.h"

namespace rec {
namespace gui {

void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled);
void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled, const string& pressed);

void setButtonImagesAlternate(DrawableButton* b, const string& normal,
                              const string& disabled, const string& alternate);


#define SET_BUTTON_IMAGES2(B, NORMAL) \
  setButtonImages(B,                                    \
                  BINARY_DATA_STRING(NORMAL ## _svg),   \
                  BINARY_DATA_STRING(NORMAL ## Disabled_svg))

#define SET_BUTTON_IMAGES3(B, NORMAL) \
  setButtonImages(B,                                          \
                  BINARY_DATA_STRING(NORMAL ## _svg),         \
                  BINARY_DATA_STRING(NORMAL ## Disabled_svg), \
                  BINARY_DATA_STRING(NORMAL ## Pressed_svg))

#define SET_BUTTON_IMAGES_ALTERNATE(B, NORMAL, ALTERNATE)     \
  setButtonImagesAlternate(B,                                          \
                           BINARY_DATA_STRING(NORMAL ## _svg),         \
                           BINARY_DATA_STRING(NORMAL ## Disabled_svg), \
                           BINARY_DATA_STRING(ALTERNATE ## _svg))

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ICONBUTTON__
