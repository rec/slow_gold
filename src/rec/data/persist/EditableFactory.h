#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/data/persist/TypedEditable.h"
#include "rec/data/proto/GetProtoName.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/STL.h"

#include "rec/app/Files.h"

namespace rec {
namespace persist {

class EditableFactory {
 public:
  typedef data::UntypedEditable UntypedEditable;
  typedef std::map<string, UntypedEditable*> DataMap;

  EditableFactory() {}
  virtual ~EditableFactory() { stl::deleteMapPointers(&data_); }
  template <typename Proto> TypedEditable<Proto>* get(const VirtualFile& vf);

 private:
  CriticalSection lock_;
  DataMap data_;

  DISALLOW_COPY_AND_ASSIGN(EditableFactory);
};

template <typename Proto>
TypedEditable<Proto>* EditableFactory::get(const VirtualFile& vf) {
  File file;
  string fileKey = str(file);
  DataMap::iterator i = data_.find(fileKey);
  if (i != data_.end())
    return static_cast<TypedEditable<Proto>*>(i->second);

  TypedEditable<Proto>* e = new TypedEditable<Proto>(file, vf);
  e->readFromFile();
  data_.insert(i, make_pair(fileKey, static_cast<UntypedEditable*>(e)));
  return e;
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
