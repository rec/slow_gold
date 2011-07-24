#include "rec/data/persist/Data.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace persist {

template <>
void Data<VirtualFile>::operator()(const VirtualFile& p) {
	setGlobal(p);
}

}  // namespace persist
}  // namespace rec
