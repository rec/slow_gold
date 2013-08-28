#include "rec/gui/IconButton.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {

void setButtonImages(DrawableButton* b, const char* normal,
                     const char* disabled) {
  ptr<Drawable> n(juceBinary<Drawable>(normal));
  ptr<Drawable> d(juceBinary<Drawable>(disabled));
  b->setImages(n.get(), NULL, NULL, d.get());
}

void setButtonImages(DrawableButton* b, const char* normal,
                     const char* disabled, const char* pressed) {
  ptr<Drawable> n(juceBinary<Drawable>(normal));
  ptr<Drawable> d(juceBinary<Drawable>(disabled));
  ptr<Drawable> p(juceBinary<Drawable>(pressed));
  b->setImages(n.get(), NULL, p.get(), d.get());
}

}  // namespace gui
}  // namespace rec
