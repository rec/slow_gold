#ifndef __REC_DATA_GROUPER__
#define __REC_DATA_GROUPER__

#include "rec/base/base.h"

namespace rec {
namespace data {

class Action;
class Editable;

// A function that identifies whether the current action can be grouped with a
// previous action.  If the second action is NULL, it returns true if there is
// any possibility that this item will be grouped with other items.  If it is
// not NULL, then the two Actions will be grouped together into the first one if
// possible, and true returned, else false will be returned and the Action will
// not be changed.

typedef bool (*ActionGrouper)(const Action& from, Action* to, const Editable*);

typedef bool (*CanGroup)(Action*);

bool actionGrouper(const Action& from, Action* to, const Editable*);
inline bool canGroup(Action*) { return true; }

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_GROUPER__
