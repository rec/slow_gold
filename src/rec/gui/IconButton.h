#ifndef __REC_GUI_ICONBUTTON__
#define __REC_GUI_ICONBUTTON__

#include "rec/base/base.h"

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

void setButtonImages(DrawableButton* b, const char* normal,
                     const char* disabled);
void setButtonImages(DrawableButton* b, const char* normal,
                     const char* disabled, const char* pressed);

#define SET_BUTTON_IMAGES2(B, NORMAL) \
  setButtonImages<NORMAL, NORMAL ## Disabled>(B)

#define SET_BUTTON_IMAGES3(B, NORMAL) \
  setButtonImages<NORMAL, NORMAL ## Disabled, NORMAL ## Pressed>(B)

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ICONBUTTON__
