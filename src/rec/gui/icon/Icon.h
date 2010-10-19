#ifndef __REC_GUI_ICON__
#define __REC_GUI_ICON__

#include <map>

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {
namespace icon {

const juce::Drawable* getIcon(const string& n);

}  // namespace icon
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ICON__
