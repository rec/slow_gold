#ifndef __REC_GUI_ICON__
#define __REC_GUI_ICON__

#include <map>

#include "rec/base/base.h"

namespace rec {
namespace gui {
namespace icon {

juce::Drawable* createFromImageData(const char* data, int len);
void deleteIcons();

// Not in use.
const juce::Drawable* getIcon(const string& n);

}  // namespace icon
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ICON__
