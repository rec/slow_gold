#pragma once

#include "rec/base/base.h"
#include "rec/gui/Orientation.pb.h"

namespace rec {
namespace gui {

using Orientation = OrientationProto::Orientation;
static const auto HORIZONTAL = OrientationProto::HORIZONTAL;
static const auto VERTICAL = OrientationProto::VERTICAL;

}  // namespace gui
}  // namespace rec
