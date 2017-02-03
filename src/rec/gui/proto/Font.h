#pragma once

#include "rec/base/base.h"
#include "rec/gui/proto/Font.pb.h"

namespace rec {
namespace gui {

Font makeFont(const FontProto&, float baseHeight);

}  // namespace gui
}  // namespace rec

