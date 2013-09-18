#ifndef __REC_GUI_PROTO_COMBOBOX__
#define __REC_GUI_PROTO_COMBOBOX__

#include "rec/base/base.h"
#include "rec/gui/proto/ComboBox.pb.h"
#include "rec/gui/proto/Constants.h"

namespace rec {
namespace gui {

unique_ptr<juce::ComboBox> makeComboBox(const ComboBoxProto&,
                                        const Constants&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_COMBOBOX__
