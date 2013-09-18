#ifndef __REC_GUI_PROTO_CONSTANTS__
#define __REC_GUI_PROTO_CONSTANTS__

#include <unordered_map>

#include "rec/base/base.h"
#include "rec/gui/proto/Constants.pb.h"

namespace rec {
namespace gui {

typedef std::unordered_map<string, double> ConstantsMap;

ConstantsMap makeConstantsMap(const Constants&);

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_CONSTANTS__
