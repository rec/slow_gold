#include "rec/gui/IconButton.h"

namespace rec {
namespace gui {

void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled) {
  ptr<Drawable> n(construct<Drawable>(normal));
  ptr<Drawable> d(construct<Drawable>(disabled));
  b->setImages(n.get(), NULL, NULL, d.get());
}

void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled, const string& pressed) {
  ptr<Drawable> n(construct<Drawable>(normal));
  ptr<Drawable> d(construct<Drawable>(disabled));
  ptr<Drawable> p(construct<Drawable>(pressed));
  b->setImages(n.get(), NULL, p.get(), d.get());
}

}  // namespace gui
}  // namespace rec
