#ifndef __REC_GUI_PROTO_LABEL__
#define __REC_GUI_PROTO_LABEL__

#include "rec/base/base.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Label.pb.h"
#include "rec/gui/SimpleLabel.h"

namespace rec {
namespace gui {

unique_ptr<SimpleLabel> makeLabel(const LabelProto&, const Constants&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_LABEL__
