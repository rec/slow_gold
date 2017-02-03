#include "rec/widget/Widget.h"

namespace rec {
namespace widget {

const Colors& getColors(const State& state, const StateColors* stateColors,
                                                const Colors& defaultColors) {
    if (stateColors) {
        State::MouseState mouse = state.mouse();
        do {
            bool selected = state.selected();
            do {
                const Colors& colors = (*stateColors)[mouse][selected];
                if (colors.color_size())
                    return colors;
                selected = !selected;
            } while (!selected);
            mouse = (State::MouseState) (mouse - 1);
        } while (mouse != State::MouseState_MIN);
    }
    return defaultColors;
}

}  // namespace widget
}  // namespace rec
