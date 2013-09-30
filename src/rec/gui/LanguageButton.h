#ifndef __REC_GUI_LANGUAGEBUTTON__
#define __REC_GUI_LANGUAGEBUTTON__

#include "rec/app/LanguageListener.h"
#include "rec/gui/DisableableComponent.h"

namespace rec {
namespace gui {

class LanguageButton : public DrawableButton,
                       public DisableableComponent,
                       public app::LanguageListener {
 public:
  LanguageButton(const String& name, const String& tooltip,
                 DrawableButton::ButtonStyle s = DrawableButton::ImageFitted);

  virtual void languageChanged();

  // Shadows :-( parent method.
  void setTooltip(const String&);
  void setTooltip(const string&);

 private:
  string tooltip_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(LanguageButton);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LANGUAGEBUTTON__
