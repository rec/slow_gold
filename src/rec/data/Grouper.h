#ifndef __REC_DATA_GROUPER__
#define __REC_DATA_GROUPER__

#include "rec/base/base.h"

namespace rec {
namespace data {

class Action;
class Editable;

bool groupCloseActions(Action* to, const Action* from, const Editable*);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_GROUPER__
