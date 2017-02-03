#include "rec/gui/LanguageButton.h"

namespace rec {
namespace gui {

LanguageButton::LanguageButton(const String& name,
                                                              const String& tooltip,
                                                              DrawableButton::ButtonStyle style)
        : DrawableButton(name, style), tooltip_(str(tooltip)) {
}

void LanguageButton::languageChanged() {
    DrawableButton::setTooltip(Trans(tooltip_));
}

void LanguageButton::setTooltip(const String& t) {
    setTooltip(str(t));
}

void LanguageButton::setTooltip(const string& t) {
    tooltip_ = t;
    languageChanged();
}

}  // namespace gui
}  // namespace rec
