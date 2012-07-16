#include "rec/data/DataOps.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataMap.h"
#include "rec/data/Opener.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace data {

Data* getData(const string& typeName, const VirtualFile& vf) {
  return getDataCenter().map_->getData(typeName, vf);
}

const VirtualFile& global() {
  static const VirtualFile vf = file::makeVirtualFile(VirtualFile::GLOBAL);
  return vf;
}

const VirtualFile& noData() {
  static const VirtualFile vf;
  return vf;
}

void setProto(const Message& m, Undoable undoable) {
  setProto(m, global(), undoable);
}

Message* cloneMessage(Data* data) {
  return Reader<Message>(data).cloneMessage();
}

void setProto(const Message& m, Data* data, Undoable undoable) {
  Opener<Message>(data, undoable)->CopyFrom(m);
}

void setProto(const Message& m, const VirtualFile& vf, Undoable undoable) {
  setProto(m, getData(getTypeName(m), vf), undoable);
}



}  // namespace data
}  // namespace rec
