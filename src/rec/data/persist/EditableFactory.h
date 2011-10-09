#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/data/persist/TypedEditable.h"
#include "rec/data/proto/GetProtoName.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/STL.h"

#include "rec/app/Directory.h"

namespace rec {
namespace persist {

class EditableFactory {
 public:
  typedef data::UntypedEditable UntypedEditable;
  typedef std::map<string, UntypedEditable*> DataMap;

  EditableFactory() {}
  virtual ~EditableFactory() { stl::deleteMapPointers(&data_); }

  virtual void needsUpdate(UntypedEditable* data) = 0;
  template <typename Proto> TypedEditable<Proto>* get(const VirtualFile& vf);

 private:
  CriticalSection lock_;
  DataMap data_;

  DISALLOW_COPY_AND_ASSIGN(EditableFactory);
};

template <typename Proto>
TypedEditable<Proto>* EditableFactory::get(const VirtualFile& vf) {
  File file = getShadowFile(vf, str(data::proto::getName<Proto>()));
  string fileKey = str(file);
  DataMap::iterator i = data_.find(fileKey);
  UntypedEditable* editable;
  if (i != data_.end()) {
    editable = i->second;
  } else {
    editable = new TypedEditable<Proto>(file, this);
    editable->readFromFile();
    data_.insert(i, make_pair(fileKey, editable));
  }

  return static_cast<TypedEditable<Proto>*>(editable);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
