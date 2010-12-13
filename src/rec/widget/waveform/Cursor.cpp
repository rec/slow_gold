#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Colors.h"

using namespace rec::gui;

namespace rec {
namespace widget {
namespace waveform {

namespace {


typedef StateColors[Cursor::Type_ARRAYSIZE] CursorStateColors;

const CursorStateColors& getStateColors() {
  static CursorStateColors colors = {
    {
      { 0x0, 0x0 },  // NONE
      { 0x0, 0x0 },  // DOWN
      { 0x0, 0x0 },  // HOVERING
    },  // NONE

    {
      { 0x0, 0x0 },  // NONE
      { 0x0, 0x0 },  // DOWN
      { 0x0, 0x0 },  // HOVERING
    },  // PLAYBACK_POSITION

    {
      { 0x0, 0x0 },  // NONE
      { 0x0, 0x0 },  // DOWN
      { 0x0, 0x0 },  // HOVERING
    },  // LOOP_START

    {
      { 0x0, 0x0 },  // NONE
      { 0x0, 0x0 },  // DOWN
      { 0x0, 0x0 },  // HOVERING
    },  // LOOP_END

  return colors;
}

}  // namespace


}  // namespace waveform
}  // namespace widget
}  // namespace rec
