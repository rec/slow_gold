#include "rec/gui/proto/Constants.h"

namespace rec {
namespace gui {

ConstantsMap makeConstantsMap(const Constants& constants) {
  ConstantsMap map;
  for (auto& constant: constants.constant())
    map[constant.name()] = constant.value();
  return map;
}

}  // namespace gui
}  // namespace rec
