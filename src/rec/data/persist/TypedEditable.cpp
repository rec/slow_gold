#include "rec/data/persist/TypedEditable.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace persist {

template <>
void TypedEditable<VirtualFile>::operator()(const VirtualFile& p) {
	setGlobal(p);
}

}  // namespace persist
}  // namespace rec
