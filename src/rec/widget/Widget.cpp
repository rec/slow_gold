#include "rec/widget/Widget.h"

namespace rec {
namespace widget {

const Colors& getColors(const State& state, const StateColors* stateColors,
                        const Colors& defaultColors) {
  if (stateColors) {
    State::MouseState mouse = state.mouse_state();
    do {
      bool selected = state.selected();
      do {
        const Colors& colors = stateColors[mouse][selected];
        if (colors.color_size())
          return colors;
        selected = !selected;
      } while (!selected);
    } while (mouse-- != State::MouseState_MIN);
  }
  return defaultColors;
}

}  // namespace widget
}  // namespace rec
