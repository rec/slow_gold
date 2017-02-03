#pragma once

#include "rec/app/LanguageListener.h"
#include "rec/util/Disableable.h"

namespace rec {
namespace gui {

class LanguageButton : public DrawableButton,
                                              public Disableable,
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
