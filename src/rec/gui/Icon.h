#ifndef __REC_GUI_ICON__
#define __REC_GUI_ICON__

#include <map>

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {

const juce::Drawable* getIcon(const string& n);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ICON__
