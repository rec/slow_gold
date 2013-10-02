#ifndef __REC_GUI_ORIENTATION__
#define __REC_GUI_ORIENTATION__

#include "rec/base/base.h"
#include "rec/gui/Orientation.pb.h"

namespace rec {
namespace gui {

typedef OrientationProto::Orientation Orientation;
static const auto HORIZONTAL = OrientationProto::HORIZONTAL;
static const auto VERTICAL = OrientationProto::VERTICAL;

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ORIENTATION__
