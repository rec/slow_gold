#ifndef __REC_UTIL_UNTYPEDDATALISTENER__
#define __REC_UTIL_UNTYPEDDATALISTENER__

#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

class UntypedDataListener : public Listener<const Message&>,
                            public DataFileListener {
 public:
  explicit UntypedDataListener(const string& typeName,
                               Scope scope = FILE_SCOPE);
  virtual ~UntypedDataListener();

  virtual void operator()(const Message& m) = 0;
  virtual void operator()(DataFile);

  const string& typeName() const { return typeName_; }
  Data* getData() const { Lock l(lock_); return data_; }

  static void setGlobalDataFile(DataFile);

 protected:
  CriticalSection lock_;

 private:
  const Scope scope_;
  const string typeName_;
  Data* data_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedDataListener);
};

class UntypedGlobalDataListener : public UntypedDataListener {
 public:
  explicit UntypedGlobalDataListener(const string& typeName)
      : UntypedDataListener(typeName, GLOBAL_SCOPE) {
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedGlobalDataListener);
};

}  // namespace data

using data::UntypedDataListener;
using data::UntypedGlobalDataListener;

}  // namespace rec

#endif  // __REC_UTIL_UNTYPEDDATALISTENER__
