#include "rec/data/DataOps.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataMap.h"
#include "rec/data/Opener.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

Data* getData(const string& typeName, const VirtualFile& vf) {
    return getDataCenter()->dataMap()->getData(typeName, vf);
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
    setProto(m, getData(m.GetTypeName(), vf), undoable);
}



}  // namespace data
}  // namespace rec
