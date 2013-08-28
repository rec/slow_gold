#ifndef __REC_GUI_ICONBUTTON__
#define __REC_GUI_ICONBUTTON__

#include "rec/util/Binary.h"

namespace rec {
namespace gui {

template <typename Normal, typename Disabled>
void setButtonImages(DrawableButton* b) {
  b->setImages(ptr<Drawable>(Normal::create()).get(),
               NULL,
               NULL,
               ptr<Drawable>(Disabled::create()).get());
}

template <typename Normal, typename Disabled, typename Pressed>
void setButtonImages(DrawableButton* b) {
  b->setImages(ptr<Drawable>(Normal::create()).get(),
               NULL,
               ptr<Drawable>(Pressed::create()).get(),
               ptr<Drawable>(Disabled::create()).get());
}

void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled);
void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled, const string& pressed);

#define SET_BUTTON_IMAGES2(B, NORMAL) \
  setButtonImages(B,                                    \
                  BINARY_DATA_STRING(NORMAL ## _svg),   \
                  BINARY_DATA_STRING(NORMAL ## Disabled_svg))

#define SET_BUTTON_IMAGES3(B, NORMAL) \
  setButtonImages(B,                                          \
                  BINARY_DATA_STRING(NORMAL ## _svg),         \
                  BINARY_DATA_STRING(NORMAL ## Disabled_svg), \
                  BINARY_DATA_STRING(NORMAL ## Pressed_svg))

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ICONBUTTON__
