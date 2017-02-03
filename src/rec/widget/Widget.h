#pragma once

#include "rec/base/base.h"
#include "rec/widget/Widget.pb.h"

namespace rec {
namespace widget {

using namespace rec::gui;

typedef Colors StateColors[State::MouseState_ARRAYSIZE][2];

const Colors& getColors(const State& state,
                                                const StateColors* stateColors,
                                                const Colors& dflt);

}  // namespace widget
}  // namespace rec

