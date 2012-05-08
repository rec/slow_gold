#include "rec/data/DataOps.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataMap.h"

namespace rec {
namespace data {

Data* getData(const string& typeName, DataFile vf) {
  return getDataCenter().map_->getData(typeName, vf);
}

}  // namespace data
}  // namespace rec
