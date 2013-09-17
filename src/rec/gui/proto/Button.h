#ifndef __REC_GUI_PROTO_BUTTON__
#define __REC_GUI_PROTO_BUTTON__

#include "rec/base/base.h"
#include "rec/gui/proto/Button.pb.h"
#include "rec/gui/LanguageButton.h"

namespace rec {
namespace gui {

unique_ptr<LanguageButton> makeButton(const ButtonProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_BUTTON__
