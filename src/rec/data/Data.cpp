#include "rec/data/Data.h"
#include "rec/data/EditableUpdater.h"

namespace rec {
namespace data {

File editableFile(const string& typeName, const VirtualFile* vf) {
  return getShadowFile(vf ? *vf : file::none(), str(typeName));
}

const string emptyTypeName() { return ":empty:"; }

UntypedEditable* editable(const string& typeName, const VirtualFile* vf) {
  EditableUpdater* updater = EditableUpdater::instance();
  File file = editableFile(typeName, vf);
  string key = vf ? str(file) : emptyTypeName() + typeName;

  Lock l(updater->lock());
  EditableMap::const_iterator i = updater->map()->find(key);
  if (i != updater->map()->end())
    return i->second;

  ptr<UntypedEditable> e(updater->dataRegistry()->make(typeName, file, vf));
  if (e)
    (*updater->map())[key] = e.get();

  return e.transfer();
}



}  // namespace data
}  // namespace rec
