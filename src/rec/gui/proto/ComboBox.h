#ifndef __REC_GUI_PROTO_COMBOBOX__
#define __REC_GUI_PROTO_COMBOBOX__

#include "rec/base/base.h"
#include "rec/gui/proto/ComboBox.pb.h"

namespace rec {
namespace gui {

unique_ptr<juce::ComboBox> makeComboBox(const ComboBoxProto&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_COMBOBOX__