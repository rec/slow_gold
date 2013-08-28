#include "rec/gui/IconButton.h"

namespace rec {
namespace gui {

void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled) {
  ptr<Drawable> n(construct<Drawable>(normal));
  ptr<Drawable> d(construct<Drawable>(disabled));
  b->setImages(n.get(), nullptr, nullptr, d.get());
}

void setButtonImages(DrawableButton* b, const string& normal,
                     const string& disabled, const string& pressed) {
  ptr<Drawable> n(construct<Drawable>(normal));
  ptr<Drawable> d(construct<Drawable>(disabled));
  ptr<Drawable> p(construct<Drawable>(pressed));
  b->setImages(n.get(), nullptr, p.get(), d.get());
}

void setButtonImagesAlternate(DrawableButton* b, const string& normal,
                              const string& disabled, const string& alternate) {
  ptr<Drawable> n(construct<Drawable>(normal));
  ptr<Drawable> d(construct<Drawable>(disabled));
  ptr<Drawable> a(construct<Drawable>(alternate));
  b->setImages(n.get(), nullptr, nullptr, d.get(), a.get());
}


}  // namespace gui
}  // namespace rec
