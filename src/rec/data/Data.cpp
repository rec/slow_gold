#include "rec/data/Data.h"
#include "rec/data/DataUpdater.h"

namespace rec {
namespace data {

File editableFile(const string& typeName, const VirtualFile* vf) {
  return getShadowFile(vf ? *vf : file::none(), str(typeName));
}

const string emptyTypeName() { return ":empty:"; }

Data* getData(const string& typeName, const VirtualFile* vf) {
  Lock l(lock_);

  File file = editableFile(typeName, vf);
  string key = vf ? str(file) : emptyTypeName() + typeName;

  Map::iterator i = map_.find(key);
  if (i != map_.end())
    return i->second;


  DataUpdater* updater = DataUpdater::instance();

  Lock l(updater->lock());
  EditableMap::const_iterator i = updater->map()->find(key);

  ptr<Data> data(updater->dataRegistry()->make(typeName, file, vf));
  if (data)
    (*updater->map())[key] = data.get();

  return data.transfer();
}



}  // namespace data
}  // namespace rec
