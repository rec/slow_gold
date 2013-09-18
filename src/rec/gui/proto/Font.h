#ifndef __REC_GUI_PROTO_FONT__
#define __REC_GUI_PROTO_FONT__

#include "rec/base/base.h"
#include "rec/gui/proto/Font.pb.h"

namespace rec {
namespace gui {

Font makeFont(const FontProto&, float baseHeight);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_FONT__
