#include "rec/data/DataOps.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataMap.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace data {

static VirtualFile makeGlobal() {
  VirtualFile vf;
  vf.set_type(VirtualFile::GLOBAL);
  return vf;
}

Data* getData(const string& typeName, const VirtualFile& vf) {
  return getDataCenter().map_->getData(typeName, vf);
}

const VirtualFile& global() {
  static const VirtualFile vf = makeGlobal();
  return vf;
}

const VirtualFile& noData() {
  static const VirtualFile vf;
  return vf;
}

}  // namespace data
}  // namespace rec
