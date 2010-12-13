#ifndef __REC_WIDGET_WIDGET__
#define __REC_WIDGET_WIDGET__

#include "rec/base/base.h"
#include "rec/widget/Widget.pb.h"
#include "rec/gui/Color.h"

namespace rec {
namespace widget {

typedef Colors[State::MouseState_ARRAYSIZE][2] StateColors;

const Colors& getColors(const State& state,
                        const StateColors* stateColors,
                        const Colors& dflt = gui::color::getDefaultColors());

}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WIDGET__
