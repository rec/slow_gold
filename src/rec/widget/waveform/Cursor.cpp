#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Color.h"

using namespace rec::gui;
using namespace rec::gui::color;

namespace rec {
namespace widget {
namespace waveform {

namespace {

typedef StateColors CursorStateColors[CursorProto::Type_ARRAYSIZE];

const CursorStateColors& getStateColors() {
  static CursorStateColors colors = {
    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // NONE

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // PLAYBACK_POSITION

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // LOOP_START

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // LOOP_END
  };

  return colors;
}

}  // namespace


}  // namespace waveform
}  // namespace widget
}  // namespace rec
